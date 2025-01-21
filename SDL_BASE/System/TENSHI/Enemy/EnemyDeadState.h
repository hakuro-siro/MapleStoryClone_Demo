//
// Created by binetsu on 9/7/24.
//

#include "System/Component/FSM/State.h"
#include "System/Utility/Event.h"
#include "EnemyState.h"
#include <vector>

class EnemyDeadState : public EnemyState{
public:
    EnemyDeadState(class Enemy* enemy,class StateMachine* machine);
    ~EnemyDeadState() override;
    void EnterState() override;
    void ExitState() override;
    void UpdateState(float deltaTime) override;

};
