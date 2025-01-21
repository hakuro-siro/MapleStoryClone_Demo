//
// Created by binetsu on 5/15/24.
//

#include <vector>
#include "System/Utility/Math.h"
#include "System/Process/IProcess.h"

#pragma once
class GameObject : public  IProcess {

public:
    std::string GameObjectName = "GameObject";

    GameObject();
    GameObject(Vector2 pos);
    virtual ~GameObject();

    void Update(float deltaTime) override;
    void UpdateComponents(float deltaTime);

    bool Initialize() override;
    void Finalize() override;

    // Getters/setters
    void SetPosition(Vector2 pos);
    void SetScale(float scale) { mScale = scale; }
    void SetWidth(int width) { mWidth = width; }
    void SetHeight(int height) { mHeight = height; }

    void SetRotation(float rotation) { mRotation = rotation; }

    Vector2 GetPosition() { return mPosition; }
    int GetWidth() { return mWidth; }
    int GetHeight() { return mHeight; }
    float GetRotation() const { return mRotation; }

    template<typename T>
    T* GetComponent() {
        for(auto& component : mComponents){
            if(auto casted = dynamic_cast<T*>(component)){
                return dynamic_cast<T*>(component);
            }
        }
        return nullptr;
    }

    // Add/remove components
    void AddComponent(class Component& component);
    void RemoveComponent(class Component& component);

    virtual void UpdateObject(float deltaTime);

    virtual void OnTriggerStayEnter(class Collider& other);
    virtual void OnTriggerEnter(class Collider& other);
    virtual void OnColliderEnter(class Collider& other);
    virtual void OnTriggerExit(class Collider& other);
    virtual void OnColliderExit(class Collider& others);


    Collider* CurrentGround = nullptr;

    bool Flip = false;
protected:
    Vector2 mPosition;
    int mWidth = 100;
    int mHeight = 100;
private:
    float mScale;
    float mRotation;
#ifdef _DEBUG
    class DebugRay* GameObjectPositionDebugRay;
#endif
    std::vector<class Component*> mComponents;

};
