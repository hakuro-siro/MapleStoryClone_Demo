//
// Created by binetsu on 1/16/25.
//
#include <vector>
#include "System/Utility/Event.h"

using namespace std;

class IinteractableObject{
public:
    IinteractableObject();
    ~IinteractableObject();
    virtual void Interact() = 0;
protected:
    std::vector<Obserable*> Subscribes;
};