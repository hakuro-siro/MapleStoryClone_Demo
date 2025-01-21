//
// Created by binetsu on 9/10/24.
//

#include "System/Component/Component.h"
#include "System/Utility/Math.h"
#pragma once
class Rigidbody : public Component {
public:
    /// Construct
    Rigidbody(class GameObject* owner, int updateOrder = 100);

    ~Rigidbody();

    void Update(float deltaTime) override;
    bool CheckGround();
    void UpdatePhysics(float deltaTime);
    void UpdateGravity(float deltaTime);
    // ADD-FORCE
    void AddForce(Vector2 velocity);
    void ClearForce() { AddForceVector = Vector2::Zero; }
    void SetActive(bool isg) {Active = isg;}
    void SetmCollider(class Collider& col) { mCollider = &col;}
    bool GetActive() const {return Active;}
    Vector2 RigidVector = Vector2::Zero;

private:
    void CalculateForce(float deltaTime);
    // ACC
    Vector2 AddForceVector = Vector2::Zero;
    // Force = Velocity * Mass
    Vector2 Force = Vector2::Zero;
    float GravityForceLimit = 400;
    Vector2* GravityVector;
    Vector2 CheckGroundAPos1;
    Vector2 CheckGroundAPos2;
    Vector2 CheckGroundBPos1;
    Vector2 CheckGroundBPos2;
    Vector2 CheckGroundCPos1;
    Vector2 CheckGroundCPos2;
    class Collider* mCollider;
    float Gravity = -9.8f;
    float Mass = 2.0f;
    bool Active = false;
};


