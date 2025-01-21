
//
// Created by binetsu on 9/4/24.
//
#include <SDL2/SDL.h>
#include "PlayerJumpState.h"
#include "System/GameObject/GameObject.h"
#include "System/Utility/Math.h"
#include "System/Process/Processer.h"
#include "System/Process/InputReader.h"
#include "Player.h"
#include "System/Data/AnimSpriteData.h"
#include "System/Data/AssetPath.h"
#include "System/Process/AssetLoader.h"
#include "System/Component/AnimSpriteComponent.h"
#include "System/Component/FSM/StateMachine.h"
#include "PlayerIdleState.h"
#include "System/Physics/Rigidbody.h"
#include "System/Physics/BoxCollider.h"
#include "System/Physics/LineCollider.h"
#include "spdlog/spdlog.h"
#include "PlayerMoveState.h"
#include "PlayerSkillState.h"
#include "PlayerDoubleJumpState.h"

PlayerJumpState::PlayerJumpState(Player * player,StateMachine* machine)
        :PlayerState(),
        JumpVelocity(Vector2(0,JumpPower))
        {
            mMachine = machine;
            mPlayer = player;
            MoveInput = &Singleton<InputReader>::GetInstance().MovementInputVector;
        }

void PlayerJumpState::EnterState() {
    PlayerState::EnterState();
    StateName  = "playerjumpstate";
    //SDL_Log("Enter JumpState");
    SetSprites();
}

void PlayerJumpState::OnKeyInput(int Keycode) {
    GotoSkillState(Keycode);
}

void PlayerJumpState::GotoSkillState(int Keycode) {
    //SPDLOG_INFO("my key codee {}",Keycode);
    if(mMachine->GetSubstate()!= nullptr)
        return;
    auto KeyIter= SkillInputMap.find(Keycode);
    auto *skillState = new PlayerSkillState(mPlayer, mMachine,KeyIter->second);
    mMachine->AddSubState(skillState);
}
void PlayerJumpState::SetSprites() {
    SDL_Texture* Tex= Singleton<AssetLoader>::GetInstance().GetTexture(PLAYER_DIR+Player_Jump);
    vector<AnimSpriteData> data = Singleton<AssetLoader>::GetInstance().LoadAnimSpriteData(PLAYER_DIR+Player_Jump_Json);

    mPlayer->GetAnimSpriteComponent()->SetPosition(mPlayer->GetPosition());
    mPlayer->GetAnimSpriteComponent()->SetFlip(mPlayer->Flip);
    mPlayer->GetAnimSpriteComponent()->SetAnimFPS(static_cast<float>(data.size()));
    mPlayer->GetAnimSpriteComponent()->SetAniTextures(*Tex,data);

}

void PlayerJumpState::UpdateState(float deltaTime) {
    UpdateMovement(deltaTime);
    if(!mPlayer->Isground&&!IsJumping){
        IsJumping = true;
    }
    if(JumpVelocity.y<0){
        JumpVelocity.y += deltaTime * 9.8 * 2.5f;
    }
    else
    {
        JumpVelocity.y = 0;
    }

    mPlayer->GetRigid()->AddForce(JumpVelocity);
    //SPDLOG_INFO("{}",JumpVelocity.y);
    if(IsJumping){
        mPlayer->GetCollider()->Active = false;
    }
    if(IsJumping && mPlayer->Isground){
        if(mPlayer->CurrentGround!= nullptr){

           // SPDLOG_INFO("Exit Rule?{}",JumpVelocity.y);
            if(mPlayer->CurrentGround->GetColliderType()==LineCol){
                auto Ground = dynamic_cast<LineCollider*>(mPlayer->CurrentGround);
                // Diag!
                if((Ground->posA.y!=Ground->posB.y))
                {
                    //SPDLOG_INFO("Exit By Diagnal Ground....");
                    if(Singleton<InputReader>::GetInstance().MovementInputVector.x==0&&
                       Singleton<InputReader>::GetInstance().MovementInputVector.y==0)
                    {
                        auto* idleState = new PlayerIdleState(mPlayer,mMachine);
                        mMachine->SwitchState(idleState);
                    }else{
                        auto* moveState = new PlayerMoveState(mPlayer,mMachine);
                        mMachine->SwitchState(moveState);
                    }

                }
                else if(JumpVelocity.y>=0)
                {

                    //SPDLOG_INFO("Exit By Horizontal Ground....");
                    if(Singleton<InputReader>::GetInstance().MovementInputVector.x==0&&
                       Singleton<InputReader>::GetInstance().MovementInputVector.y==0)
                    {
                        auto* idleState = new PlayerIdleState(mPlayer,mMachine);
                        mMachine->SwitchState(idleState);
                    }else{
                        auto* moveState = new PlayerMoveState(mPlayer,mMachine);
                        mMachine->SwitchState(moveState);
                    }

                }
            }
        }
    }

}

void PlayerJumpState::UpdateMovement(float deltaTime){
    if(mPlayer->IsWall)
        return;

    position = mPlayer->GetPosition();
    CalculateMoveInput();
    CalculateMovement(deltaTime);
    position += Movement * MovementSpeed;
    mPlayer->SetPosition(position);


    mPlayer->GetCollider()->UpdateColliderData();
}

void PlayerJumpState::CalculateMovement(float deltaTime){
    if(mPlayer->IsWall)
        return;
    Movement.x = X_AxisMovement* deltaTime;
}

void PlayerJumpState::ExitState() {
    SDL_Log("Exit JumpState");
    JumpVelocity.y = 0;
    IsJumping = false;
    mPlayer->GetCollider()->Active = true;
    mPlayer->GetRigid()->ClearForce();
    PlayerState::ExitState();
}

void PlayerJumpState::OnJumpInput() {

    if(mPlayer->Isground)
        return;

    auto *doubleJumpState = new PlayerDoubleJumpState(mPlayer, mMachine);
    mMachine->SwitchState(doubleJumpState);
}

void PlayerJumpState::CalculateMoveInput(){
    MoveInput = &Singleton<InputReader>::GetInstance().MovementInputVector;

    X_AxisMovement = MoveInput->x;
    if(mPlayer->CurrentGround!= nullptr){
        if(mPlayer->CurrentGround->GetColliderType()==LineCol){
            auto Ground = dynamic_cast<LineCollider*>(mPlayer->CurrentGround);
            if(Ground->posA.y>Ground->posB.y)
            {
                if(X_AxisMovement<0)
                    Y_AxisMovement = 1;
            }
            else if(Ground->posA.y<Ground->posB.y)
            {
                if(X_AxisMovement>0)
                    Y_AxisMovement = 1;
            }
        }
    }

    if(X_AxisMovement == -1){
        mPlayer->GetAnimSpriteComponent()->SetFlip(false);
        mPlayer->Flip = false;
    }
    else if(X_AxisMovement == 1){
        mPlayer->GetAnimSpriteComponent()->SetFlip(true);
        mPlayer->Flip=true;
    }

    //SPDLOG_INFO("X : {} Y : {}",X_AxisMovement,Y_AxisMovement);
}