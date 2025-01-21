//
// Created by binetsu on 9/7/24.
//

#include "EnemyHitState.h"
#include "EnemyIdleState.h"
#include "EnemyDeadState.h"
#include "Enemy.h"
#include "System/Component/AnimSpriteComponent.h"
#include "System/Process/Processer.h"
#include "System/Process/AssetLoader.h"
#include "System/Data/AssetPath.h"
#include "iostream"
#include "System/Component/FSM/StateMachine.h"
#include "System/Process/InputReader.h"

EnemyHitState::EnemyHitState(Enemy* enemy,StateMachine* machine):
        EnemyState(enemy,machine){
}

void EnemyHitState::EnterState() {
    EnemyState::EnterState();
    // enemy 이미지 동적 로드 변경 필요
    vector<SDL_Texture*> hitTex;
    for(auto& data :mEnemy->enemyData->HitImgDIR){
        SDL_Texture* Tex= Singleton<AssetLoader>::GetInstance().GetTexture(ENEMY_DIR+data);
        hitTex.emplace_back(Tex);
    }
    mEnemy->GetAnimSpriteComponent()->SetAnimFPS(static_cast<float>(hitTex.size()));
    mEnemy->GetAnimSpriteComponent()->SetAniTextures(hitTex);
}

void EnemyHitState::GotoMovementState() {

}
void EnemyHitState::OnDeadHandled(){
    auto *deadState = new EnemyDeadState(mEnemy, mMachine);
    mMachine->SwitchState(deadState);
}

void EnemyHitState::UpdateState(float deltaTime) {
    CurrentLifeTime+=deltaTime;
    if(CurrentLifeTime>=DamageLifeTime)
    {
        auto *idleState = new EnemyIdleState(mEnemy, mMachine);
        mMachine->SwitchState(idleState);
    }
}

void EnemyHitState::ExitState() {
    EnemyState::ExitState();
}

EnemyHitState::~EnemyHitState() {

}