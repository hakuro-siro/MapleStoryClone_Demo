//
// Created by binetsu on 1/16/25.
//

#pragma once
#include "System/GameObject/GameObject.h"
#include "System/TENSHI/Player/Skill/Skill.h"
#include "System/GameObject/IinteractableObject.h"

class Portal : public GameObject , IinteractableObject
{
public:
    Portal();
    ~Portal();
    void Interact() override;
    void OnTriggerEnter(class Collider& other) override;
    void OnTriggerExit(class Collider& other) override;
    class BoxCollider* Trigger;
protected:
    bool IsPlayerOnThis = false;
};