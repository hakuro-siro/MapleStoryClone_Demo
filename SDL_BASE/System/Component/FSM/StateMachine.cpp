//
// Created by binetsu on 9/7/24.
//

#include <algorithm>
#include "StateMachine.h"
#include "State.h"
#include "spdlog/spdlog.h"

StateMachine::StateMachine(class GameObject *owner,int updateOrder):
        Component(owner,updateOrder){
}

void StateMachine::SetStartState(class State *StartState) {
    CurrentState = StartState;
    CurrentState->EnterState();
}
void StateMachine::Update(float deltaTime) {
    if(CurrentState!= nullptr&&!Switching)
        CurrentState->UpdateState(deltaTime);

    if(SubState!= nullptr&&!Switching)
        SubState->UpdateState(deltaTime);

}

void StateMachine::SwitchState(State *DesireState) {
    //SPDLOG_INFO("Switch State {} to {}",CurrentState->StateName,DesireState->StateName);
    Switching  = true;
    CurrentState ->ExitState();
    delete CurrentState;
    CurrentState = DesireState;
    CurrentState ->EnterState();
    Switching = false;
}

void StateMachine::AddSubState(State *state)
{
    SubState = state;
    SubState->EnterState();
}

void StateMachine::DeleteSubState(State *state)
{
    Switching  = true;
    SubState = nullptr;
    delete state;
    Switching  = false;
}


StateMachine::~StateMachine() {
    if(CurrentState != nullptr)
        CurrentState ->ExitState();
    if(SubState!= nullptr)
        SubState ->ExitState();
    delete CurrentState;
    delete SubState;
}