//
// Created by binetsu on 9/7/24.
//

#pragma once
#include "System/Component/Component.h"
#include "System/Component/FSM/State.h"
#include "System/Utility/Event.h"
#include <vector>
using namespace std;

class PlayerState : public State{

public:
    PlayerState();
    void EnterState() override;
    void ExitState() override;
    void RefreshState() override;
    virtual void SetSprites() {}
    virtual void OnJumpInput();
    virtual void OnKeyInput(int Keycode);
protected:
    std::vector<Obserable*> Subscribes;
};
