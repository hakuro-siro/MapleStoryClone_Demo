//
// Created by binetsu on 9/7/24.
//

#pragma once
#include "System/Component/Component.h"
#include <vector>
#include <string>
using namespace std;
class State{

public:
    State();
    virtual ~State();

    virtual void EnterState();
    virtual void RefreshState() {}
    virtual void UpdateState(float deltaTime);
    virtual void ExitState();
    std::string StateName = "state";
protected:
    vector<Component*> StateComponent;
};
