//
// Created by binetsu on 9/7/24.
//

#include "System/Component/Component.h"
#include "System/Component/FSM/State.h"
class StateMachine : public Component {

public:
    //Constructor
    StateMachine(class GameObject *owner, int updateOrder = 10);
    void Update(float deltaTime) override;
    void SetStartState(State* StartState);
    void SwitchState(State* DesireState);
    void AddSubState(State* state);
    void DeleteSubState(State* state);
    State* GetSubstate() { return  SubState;}
    void ReFresh() {
        if(!Switching)
            CurrentState->RefreshState();
    };
    void EndState() {
        Switching  = true;
        CurrentState ->ExitState();
        delete CurrentState;
        CurrentState = nullptr;
    }
    ~StateMachine();
private:
    bool Switching = false;
    State* CurrentState = nullptr;
    State* SubState = nullptr;
};

