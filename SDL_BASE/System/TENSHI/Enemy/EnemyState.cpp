//
// Created by binetsu on 11/12/24.
//

#include "EnemyState.h"
#include "Enemy.h"
#include "System/Process/InputReader.h"
#include "System/TENSHI/Damage/Health.h"
#include "System/Component/FSM/StateMachine.h"

EnemyState::EnemyState(Enemy* enemy,StateMachine* machine) {
    mMachine = machine;
    mEnemy = enemy;
}
void EnemyState::EnterState() {
    auto* DamageEvent = new Obserable(
            &mEnemy->GetHealth()->OnDamaged,
            mEnemy->GetHealth()->OnDamaged.Subscribe([this](int){
                OnDamageHandled();
            }));
    auto* DeadEvent = new Obserable(
            &mEnemy->GetHealth()->OnDead,
            mEnemy->GetHealth()->OnDead.Subscribe([this](int){
                OnDeadHandled();
            }));
    Subscribes.emplace_back(DamageEvent);
    Subscribes.emplace_back(DeadEvent);
}

void EnemyState::ExitState() {
    for (auto &observe: Subscribes) {
        observe->event->UnSubscribe(observe->key);
    }
    Subscribes.clear();
}
