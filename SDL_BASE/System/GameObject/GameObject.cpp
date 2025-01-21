//
// Created by binetsu on 5/15/24.
//

#include "GameObject.h"
#include "System/Process/Processer.h"
#include "System/Component/Component.h"
#include "System/Physics/Collider.h"
#include "System/Component/SpriteComponent.h"
#include "System/Utility/DebugRay.h"
#include <spdlog/spdlog.h>
#include <algorithm>

/// Like Unity Gameobject
GameObject::GameObject():
        mPosition(Vector2::Zero)
        , mScale(1.0f)
        , mRotation(0.0f)
{
}
GameObject::GameObject(Vector2 pos) {
    SetPosition(pos);
}


GameObject::~GameObject()
{
    SPDLOG_INFO("Delete {}",GameObjectName);
    // Need to delete components
    // Because ~Component calls RemoveComponent, need a different style loop
    while (!mComponents.empty())
    {
        delete mComponents.back();
    }
#ifdef  _DEBUG
    delete GameObjectPositionDebugRay;
#endif
}

bool GameObject::Initialize() {
    Singleton<Processer>::GetInstance().AddGameObject(this);
    IProcess::Initialize();

#ifdef _DEBUG
    GameObjectPositionDebugRay = new DebugRay();

    GameObjectPositionDebugRay->CreateRayObject(
           mPosition.x-5,mPosition.y-5,10,10,Bcolor);
#endif

    return true;
}

void GameObject::Finalize() {
    //Singleton<Processer>::GetInstance().RemoveGameObject(this);
}

/*
 * Update :
 * Component
 * Main Logic
 */
void GameObject::Update(float deltaTime)
{
    UpdateComponents(deltaTime);
    UpdateObject(deltaTime);

#ifdef _DEBUG
    GameObjectPositionDebugRay->UpdateRayObject(mPosition.x-5,mPosition.y-5,10,10);
#endif
}

void GameObject::SetPosition(Vector2 pos) {
    mPosition = pos;
}

void GameObject::UpdateComponents(float deltaTime)
{
    for (auto comp : mComponents)
    {
        comp->Update(deltaTime);
    }
}

void GameObject::UpdateObject(float deltaTime)
{

}


void GameObject::AddComponent(Component& component)
{
    // Find the insertion point in the sorted vector
    // (The first element with a order higher than me)
    int myOrder = component.GetUpdateOrder();
    auto iter = mComponents.begin();
    for (;
            iter != mComponents.end();
            ++iter)
    {
        if (myOrder < (*iter)->GetUpdateOrder())
        {
            break;
        }
    }

    // Inserts element before position of iterator
    mComponents.insert(iter, &component);
}

void GameObject::RemoveComponent(Component& component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), &component);
    if (iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}


void GameObject::OnColliderEnter(Collider& other) {

}
void GameObject::OnColliderExit(Collider& other) {

}
void GameObject::OnTriggerEnter(Collider& other) {

}
void GameObject::OnTriggerStayEnter(Collider& other) {

}
void GameObject::OnTriggerExit(Collider& other) {

}