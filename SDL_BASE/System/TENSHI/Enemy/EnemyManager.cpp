//
// Created by binetsu on 12/6/24.
//


#include "EnemyManager.h"
#include "spdlog/spdlog.h"
#include "System/Utility/Singleton.h"
#include "System/Process/AssetLoader.h"

RecallEnemy::RecallEnemy(EnemyData *data):
        mData(data){

}
RecallEnemy::~RecallEnemy(){

}
EnemyManager::EnemyManager(class GameObject *owner, int updateOrder)
        : Component(owner){

}


void EnemyManager::Update(float deltaTime) {

    for(auto enemy : mRecallEnemys){
        enemy->CurrentTime+=deltaTime;
        if(enemy->CurrentTime>=enemy->ReviveTime){
            mReviveEnemys.emplace_back(enemy);
        }
    }
    for(auto enemy : mReviveEnemys){
        Singleton<AssetLoader>::GetInstance().LoadEnemy(enemy->mData,this);

        auto iter = std::find(mRecallEnemys.begin(), mRecallEnemys.end(), enemy);
        if (iter != mRecallEnemys.end())
        {
            // Swap to end of vector and pop off (avoid erase copies)
            std::iter_swap(iter, mRecallEnemys.end() - 1);
            mRecallEnemys.pop_back();
        }
    }
    mReviveEnemys.clear();
    //SPDLOG_INFO("Recalling {}",mRecallEnemys.size());
}
EnemyManager::~EnemyManager(){

}
