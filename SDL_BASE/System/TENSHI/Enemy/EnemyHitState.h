//
// Created by binetsu on 9/7/24.
//

#include "System/Component/FSM/State.h"
#include "System/Utility/Event.h"
#include "EnemyState.h"
#include <vector>

class EnemyHitState : public EnemyState{
public:
    EnemyHitState(class Enemy* enemy,class StateMachine* machine);
    ~EnemyHitState() override;
    void EnterState() override;
    void ExitState() override;
    void UpdateState(float deltaTime) override;

    void OnDeadHandled() override;
    float DamageLifeTime = 0.3f;
    float CurrentLifeTime = 0;
private:
    void GotoMovementState();
};
