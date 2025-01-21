//
// Created by binetsu on 9/7/24.
//

#pragma once
#include "System/Component/Component.h"
#include "System/Component/FSM/State.h"
#include "System/Utility/Event.h"
#include <vector>
using namespace std;

class EnemyState : public State{

public:
    EnemyState(class Enemy* enemy,class StateMachine* machine);
    void EnterState() override;
    void ExitState() override;
    virtual void OnDamageHandled() {}
    virtual void OnDeadHandled() {}
protected:
    class Enemy* mEnemy;
    class StateMachine* mMachine;

    std::vector<Obserable*> Subscribes;
};
