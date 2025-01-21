
#pragma once
#include <utility>
#include <unordered_map>
#include "System/Component/Component.h"
#include "System/Utility/Event.h"
#include "System/Data/EnemyData.h"
#include "System/TENSHI/Enemy/Enemy.h"

class RecallEnemy{
public:
    RecallEnemy(EnemyData* data);
    ~RecallEnemy();
    EnemyData* mData = nullptr;
    float CurrentTime = 0;
    float ReviveTime = 3;
};
class EnemyManager : public Component {

public:
    EnemyManager(class GameObject* owner, int updateOrder = 10);
    ~EnemyManager();
    void Update(float deltaTime) override;
    void ClearEnemy();
protected:
    vector<EnemyData*> mEnemyData;
public:
    vector<RecallEnemy*> mRecallEnemys;
    vector<RecallEnemy*> mReviveEnemys;
    void SetEnemyData(vector<EnemyData*> data){
        mEnemyData = std::move(data);
    }
    void OnEnemyDead(EnemyData* mEnemy){
        mRecallEnemys.emplace_back(new RecallEnemy(mEnemy));
    }
};
