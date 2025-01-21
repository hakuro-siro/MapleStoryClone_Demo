//
// Created by binetsu on 9/7/24.
//

#include "EnemyDeadState.h"
#include "EnemyIdleState.h"
#include "Enemy.h"
#include "System/Component/AnimSpriteComponent.h"
#include "System/Process/Processer.h"
#include "System/Process/AssetLoader.h"
#include "System/Data/AssetPath.h"
#include "iostream"
#include "System/Component/FSM/StateMachine.h"
#include "System/Process/InputReader.h"

EnemyDeadState::EnemyDeadState(Enemy* enemy,StateMachine* machine):
        EnemyState(enemy,machine){
}

void EnemyDeadState::EnterState() {
    EnemyState::EnterState();
    // enemy 이미지 동적 로드 변경 필요
    vector<SDL_Texture*> hitTex;
    for(auto& data :mEnemy->enemyData->DeadImgDIR){
        SDL_Texture* Tex= Singleton<AssetLoader>::GetInstance().GetTexture(ENEMY_DIR+data);
        hitTex.emplace_back(Tex);
    }
    mEnemy->GetAnimSpriteComponent()->SetAnimFPS(static_cast<float>(hitTex.size()));
    mEnemy->GetAnimSpriteComponent()->SetAniTextures(hitTex);
    mEnemy->GetAnimSpriteComponent()->LoopFlag = false;
}


void EnemyDeadState::UpdateState(float deltaTime) {

    if(mEnemy->GetAnimSpriteComponent()->StopAnimationFlag
    &&mEnemy->Processing){
        mMachine->EndState();
    }
}

void EnemyDeadState::ExitState() {
    EnemyState::ExitState();
}

EnemyDeadState::~EnemyDeadState() {
    mEnemy->SetProcessing(false);
}