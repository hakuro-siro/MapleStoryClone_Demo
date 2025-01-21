//
// Created by binetsu on 9/11/24.
//

#include "Collider.h"

#pragma once

/// Triangle
class LineCollider : public Collider{
public:
    LineCollider(class GameObject* owner, int updateOrder = 10);
    ~LineCollider();
    void Update(float deltaTime) override;
    bool CheckCrash(Collider& other);
    bool UpdateColliderData() override;
    bool CheckCrash(LineCollider& other);
    void SetPosA(Vector2* vec) {
        posA = Vector2(vec->x,vec->y) + Center;};
    void SetPosB(Vector2* vec) {  posB = Vector2(vec->x,vec->y) + Center;};

    Vector2 FixObjectPos(Collider& other);
    Vector2 FixObjectPos(LineCollider& other);

    Vector2 Center;
    Vector2 posA;
    Vector2 posB;
};
