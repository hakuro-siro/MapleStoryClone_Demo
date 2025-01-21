//
// Created by binetsu on 5/15/24.
//

#include "Component.h"
#include "System/GameObject/GameObject.h"
/*
* Unity 의 component 라는 개념의 구현화
* 메인 Gameobject의 update 타이밍을 가져와서 실행한다
*/
Component::Component(GameObject* owner, int updateOrder)
        : mOwner(owner), mUpdateOrder(updateOrder) {
    // Add to actor's vector of components
    mOwner->AddComponent(*this);
}

GameObject *Component::GetOwner() {
    return mOwner;
}

Component::~Component() {
    //SPDLOG_INFO("Kill Component");
    mOwner->RemoveComponent(*this);
}

void Component::Update(float deltaTime) {
    //SPDLOG_INFO("Update Component");
}
