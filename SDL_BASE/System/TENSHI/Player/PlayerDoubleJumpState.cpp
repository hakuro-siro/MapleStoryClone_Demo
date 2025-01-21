
//
// Created by binetsu on 9/4/24.
//
#include <SDL2/SDL.h>
#include "PlayerDoubleJumpState.h"
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
#include "Skill/Skill.h"
#include "System/Process/Sprite.h"

PlayerDoubleJumpState::PlayerDoubleJumpState(Player * player,StateMachine* machine)
        :PlayerState(),
         JumpVelocity(Vector2(0,JumpPower))
{
    mMachine = machine;
    mPlayer = player;
    MoveInput = &Singleton<InputReader>::GetInstance().MovementInputVector;
    auto SkillIter= mPlayer->PlayerSkills.find("ALT");
    if(SkillIter!=mPlayer->PlayerSkills.end())
        mSkill = SkillIter->second;

}

void PlayerDoubleJumpState::EnterState() {
    PlayerState::EnterState();
    StateName  = "playerdoublejumpstate";
    //SDL_Log("Enter DoubleJumpState");
    if(mPlayer->Flip)
    {
        X_AxisMovement = 1;
    }
    else{
        X_AxisMovement = -1;
    }

    SkillGameObject = new GameObject();
    auto SkillPos = mPlayer->GetPosition();
    if(mPlayer->Flip)
        SkillPos +=Vector2(mSkill->SkillPerformPos.x,mSkill->SkillPerformPos.y);
    else
        SkillPos -=Vector2(mSkill->SkillPerformPos.x,-mSkill->SkillPerformPos.y);
    SkillGameObject->SetPosition(SkillPos);


    AnimSpriteComponent* skillImg = new AnimSpriteComponent(SkillGameObject,150);
    skillImg->GetSprite()->SetFlip(mPlayer->Flip);
    // 고쳐야함 JSON 으로
    skillImg->LoopFlag  = false;
    vector<SDL_Texture*> skilltex;
    for(auto& data : mSkill->SkillImgDIR){
        SDL_Texture* Tex= Singleton<AssetLoader>::GetInstance().GetTexture(SKILL_DIR+data);
        skilltex.emplace_back(Tex);
    }
    skillImg->SetAniTextures(skilltex);
    SetSprites();

    skillImg->AnimationEventFrame = mSkill->SkillEventFrame;
    auto* obserbFinish = new Obserable(
            &skillImg->AnimationFinishEvent,
            skillImg->AnimationFinishEvent.Subscribe([this](int){
                OnJumpFxEnd();
            }));

}

void PlayerDoubleJumpState::OnJumpFxEnd() {
    SkillGameObject->SetProcessing(false);

}

void PlayerDoubleJumpState::OnKeyInput(int Keycode) {
    GotoSkillState(Keycode);
}

void PlayerDoubleJumpState::GotoSkillState(int Keycode) {
    //SPDLOG_INFO("my key codee {}",Keycode);
    if(mMachine->GetSubstate()!= nullptr)
        return;
    auto KeyIter= SkillInputMap.find(Keycode);
    auto *skillState = new PlayerSkillState(mPlayer, mMachine,KeyIter->second);
    mMachine->AddSubState(skillState);
}
void PlayerDoubleJumpState::SetSprites() {
    SDL_Texture* Tex= Singleton<AssetLoader>::GetInstance().GetTexture(PLAYER_DIR+Player_Jump);
    vector<AnimSpriteData> data = Singleton<AssetLoader>::GetInstance().LoadAnimSpriteData(PLAYER_DIR+Player_Jump_Json);

    mPlayer->GetAnimSpriteComponent()->SetPosition(mPlayer->GetPosition());
    mPlayer->GetAnimSpriteComponent()->SetFlip(mPlayer->Flip);
    mPlayer->GetAnimSpriteComponent()->SetAnimFPS(static_cast<float>(data.size()));
    mPlayer->GetAnimSpriteComponent()->SetAniTextures(*Tex,data);

}

void PlayerDoubleJumpState::UpdateState(float deltaTime) {
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

            //SPDLOG_INFO("Exit Rule? {}",JumpVelocity.y);
            if(mPlayer->CurrentGround->GetColliderType()==LineCol){
                auto Ground = dynamic_cast<LineCollider*>(mPlayer->CurrentGround);
                // Diag!
                if(Ground->posA.y!=Ground->posB.y)
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
                else
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

void PlayerDoubleJumpState::UpdateMovement(float deltaTime){
    if(mPlayer->IsWall)
        return;

    position = mPlayer->GetPosition();
    CalculateMovement(deltaTime);
    position += Movement * MovementSpeed;
    mPlayer->SetPosition(position);
    mPlayer->GetCollider()->UpdateColliderData();
}

void PlayerDoubleJumpState::CalculateMovement(float deltaTime){
    if(mPlayer->IsWall)
        return;
    Movement.x = X_AxisMovement* deltaTime;
    MoveInput = &Singleton<InputReader>::GetInstance().MovementInputVector;

    if(mMachine->GetSubstate()==nullptr){
    if(MoveInput->x == -1){
        mPlayer->GetAnimSpriteComponent()->SetFlip(false);
        mPlayer->Flip = false;
    }
    else if(MoveInput->x == 1){
        mPlayer->GetAnimSpriteComponent()->SetFlip(true);
        mPlayer->Flip=true;
    }}
}

void PlayerDoubleJumpState::ExitState() {
    SDL_Log("Exit Double JumpState");

    JumpVelocity.y = 0;
    IsJumping = false;
    mPlayer->GetCollider()->Active = true;
    mPlayer->GetRigid()->ClearForce();
    PlayerState::ExitState();
}
