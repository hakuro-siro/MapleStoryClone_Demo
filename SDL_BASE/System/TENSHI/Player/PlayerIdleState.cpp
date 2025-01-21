//
// Created by binetsu on 9/7/24.
//

#include "PlayerIdleState.h"
#include "Player.h"
#include "System/Component/AnimSpriteComponent.h"
#include "PlayerMoveState.h"
#include "System/Process/Processer.h"
#include "System/Process/AssetLoader.h"
#include "System/Data/AssetPath.h"
#include "iostream"
#include "System/Component/FSM/StateMachine.h"
#include "System/Process/InputReader.h"
#include "PlayerJumpState.h"
#include "PlayerSkillState.h"

PlayerIdleState::PlayerIdleState(Player* player,StateMachine* machine):
PlayerState(){
    mMachine = machine;
    mPlayer = player;
}

void PlayerIdleState::EnterState() {
    StateName  = "playeridlestate";
    SDL_Log("Enter IdleState");
    PlayerState::EnterState();
    SetSprites();
}
void PlayerIdleState::SetSprites() {
    SDL_Texture* Tex = Singleton<AssetLoader>::GetInstance().GetTexture(PLAYER_DIR+Player_Idle_N);
    vector<AnimSpriteData> data =Singleton<AssetLoader>::GetInstance().LoadAnimSpriteData(PLAYER_DIR+Player_Idle_N_Json);

    mPlayer->GetAnimSpriteComponent()->SetPosition(mPlayer->GetPosition());
    mPlayer->GetAnimSpriteComponent()->SetFlip(mPlayer->Flip);
    mPlayer->GetAnimSpriteComponent()->SetAnimFPS(static_cast<float>(data.size()));
    mPlayer->GetAnimSpriteComponent()->SetAniTextures(*Tex,data);
}
void PlayerIdleState::OnJumpInput() {
    GotoJumpState();
}
void PlayerIdleState::OnKeyInput(int Keycode) {
    GotoSkillState(Keycode);
}

void PlayerIdleState::GotoSkillState(int Keycode) {
    //SPDLOG_INFO("my key codee {}",Keycode);
    if(mMachine->GetSubstate()!= nullptr)
        return;
    auto KeyIter= SkillInputMap.find(Keycode);
    auto *skillState = new PlayerSkillState(mPlayer, mMachine,KeyIter->second);
    mMachine->AddSubState(skillState);
}

void PlayerIdleState::GotoJumpState() {
    if(mPlayer->Isground) {
        auto *jumpState = new PlayerJumpState(mPlayer, mMachine);
        mMachine->SwitchState(jumpState);
    }

}

void PlayerIdleState::GotoMovementState() {
    auto* moveState = new PlayerMoveState(mPlayer,mMachine);
    mMachine->SwitchState(moveState);
}

void PlayerIdleState::UpdateState(float deltaTime) {

    if(Singleton<InputReader>::GetInstance().MovementInputVector.x!=0)
    {
        GotoMovementState();
    }

}

void PlayerIdleState::ExitState() {
    PlayerState::ExitState();
}

PlayerIdleState::~PlayerIdleState() {

}