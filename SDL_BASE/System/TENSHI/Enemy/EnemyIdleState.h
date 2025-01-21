//
// Created by binetsu on 9/7/24.
//

#include "System/Component/FSM/State.h"
#include "System/Utility/Event.h"
#include "EnemyState.h"
#include <vector>

class EnemyIdleState : public EnemyState{
public:
    EnemyIdleState(class Enemy* enemy,class StateMachine* machine);
    ~EnemyIdleState() override;
    void EnterState() override;
    void ExitState() override;
    void UpdateState(float deltaTime) override;
    void OnDamageHandled() override;

private:
    void GotoMovementState();
};
