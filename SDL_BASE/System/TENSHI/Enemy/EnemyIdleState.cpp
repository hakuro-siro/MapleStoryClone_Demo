//
// Created by binetsu on 9/7/24.
//

#include "EnemyIdleState.h"
#include "EnemyHitState.h"
#include "Enemy.h"
#include "System/Component/AnimSpriteComponent.h"
#include "System/Process/Processer.h"
#include "System/Process/AssetLoader.h"
#include "System/Data/AssetPath.h"
#include "iostream"
#include "System/Component/FSM/StateMachine.h"
#include "System/Process/InputReader.h"

EnemyIdleState::EnemyIdleState(Enemy* enemy,StateMachine* machine):
EnemyState(enemy,machine){
}

void EnemyIdleState::EnterState() {
    EnemyState::EnterState();
    // enemy 이미지 동적 로드 변경 필요
    vector<SDL_Texture*> idleTex;
    for(auto& data :mEnemy->enemyData->IdleImgDIR){
        SDL_Texture* Tex= Singleton<AssetLoader>::GetInstance().GetTexture(ENEMY_DIR+data);
        idleTex.emplace_back(Tex);
    }
    mEnemy->GetAnimSpriteComponent()->SetAnimFPS(static_cast<float>(idleTex.size()));
    mEnemy->GetAnimSpriteComponent()->SetAniTextures(idleTex);

//    mEnemy->GetAnimSpriteComponent()->SetPosition(mEnemy->GetPosition());
//    mEnemy->GetAnimSpriteComponent()->SetFlip(mEnemy->Flip);
//    mEnemy->GetAnimSpriteComponent()->SetAnimFPS(static_cast<float>(data.size()));
//    mEnemy->GetAnimSpriteComponent()->SetAniTextures(*Tex,data);
}
void EnemyIdleState::OnDamageHandled() {
    auto *hitState = new EnemyHitState(mEnemy, mMachine);
    mMachine->SwitchState(hitState);
}

void EnemyIdleState::GotoMovementState() {

}

void EnemyIdleState::UpdateState(float deltaTime) {

}

void EnemyIdleState::ExitState() {
    EnemyState::ExitState();
}

EnemyIdleState::~EnemyIdleState() {

}