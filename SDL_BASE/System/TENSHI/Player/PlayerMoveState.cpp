
//
// Created by binetsu on 9/4/24.
//
#include <SDL2/SDL.h>
#include "PlayerMoveState.h"
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
#include "PlayerJumpState.h"
#include "PlayerSkillState.h"
PlayerMoveState::PlayerMoveState(Player * player,StateMachine* machine)
        :PlayerState()
        {
            mMachine = machine;
            mPlayer = player;
            MoveInput = &Singleton<InputReader>::GetInstance().MovementInputVector;
        }

void PlayerMoveState::EnterState() {
    PlayerState::EnterState();
    StateName  = "playermovestate";
    //SDL_Log("Enter MovementState");
    SetSprites();
}

void PlayerMoveState::SetSprites() {
    SDL_Texture* Tex= Singleton<AssetLoader>::GetInstance().GetTexture(PLAYER_DIR+Player_Walk);

    vector<AnimSpriteData> data = Singleton<AssetLoader>::GetInstance().LoadAnimSpriteData(PLAYER_DIR+Player_Walk_Json);

    mPlayer->GetAnimSpriteComponent()->SetPosition(mPlayer->GetPosition());
    mPlayer->GetAnimSpriteComponent()->SetFlip(mPlayer->Flip);
    mPlayer->GetAnimSpriteComponent()->SetAnimFPS(static_cast<float>(data.size()));
    mPlayer->GetAnimSpriteComponent()->SetAniTextures(*Tex,data);

}
void PlayerMoveState::OnKeyInput(int Keycode) {
    GotoSkillState(Keycode);
}

void PlayerMoveState::GotoSkillState(int Keycode) {
    //SPDLOG_INFO("my key codee {}",Keycode);
    if(mMachine->GetSubstate()!= nullptr)
        return;
    auto KeyIter= SkillInputMap.find(Keycode);
    auto *skillState = new PlayerSkillState(mPlayer, mMachine,KeyIter->second);
    mMachine->AddSubState(skillState);
}
void PlayerMoveState::OnJumpInput() {
    GotoJumpState();
}
void PlayerMoveState::GotoJumpState() {
    if(mPlayer->Isground) {

        auto *jumpState = new PlayerJumpState(mPlayer, mMachine);

        for (auto &observe: Subscribes) {
            observe->event->UnSubscribe(observe->key);
        }
        Subscribes.clear();
        mMachine->SwitchState(jumpState);

    }

}

void PlayerMoveState::UpdateState(float deltaTime) {

    UpdateMovement(deltaTime);

    if(Singleton<InputReader>::GetInstance().MovementInputVector.x==0&&
            Singleton<InputReader>::GetInstance().MovementInputVector.y==0)
    {
        auto* idleState = new PlayerIdleState(mPlayer,mMachine);
        mMachine->SwitchState(idleState);
    }
}

void PlayerMoveState::UpdateMovement(float deltaTime){

    if(mMachine->GetSubstate()!= nullptr)
        return;

    position = mPlayer->GetPosition();
    CalculateMoveInput();
    CalculateMovement(deltaTime);
    position += Movement * MovementSpeed;

    //mPlayer->GetRigid()->AddForce(position*deltaTime);
    mPlayer->SetPosition(position);
    //mPlayer->GetRigid()->AddForce(Movement * MovementSpeed);
    mPlayer->GetCollider()->UpdateColliderData();
}

void PlayerMoveState::CalculateMovement(float deltaTime){
    if(mPlayer->IsWall){
        Movement = Vector2::Zero;
        return;
    }

    Movement.x = X_AxisMovement* deltaTime;
     Movement.y = Y_AxisMovement * deltaTime;
//    if(Y_AxisMovement==0){
//        Movement.y=0.45f*deltaTime;
//    }
}


Vector2 PlayerMoveState::GetForward() {
    return Vector2(Math::Cos(mPlayer->GetRotation()),Math::Cos(mPlayer->GetRotation()));
}

void PlayerMoveState::ExitState() {
    PlayerState::ExitState();
}


void PlayerMoveState::CalculateMoveInput(){
    MoveInput = &Singleton<InputReader>::GetInstance().MovementInputVector;

    X_AxisMovement = MoveInput->x;
    Y_AxisMovement = 0;
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