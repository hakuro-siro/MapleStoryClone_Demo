//
// Created by binetsu on 9/11/24.
//

#include "Collider.h"

#pragma once
class BoxCollider : public Collider{
public:
    BoxCollider(class GameObject* owner, int updateOrder = 10,SDL_Rect* rect = nullptr);
    ~BoxCollider();
    bool UpdateColliderData() override;
    void Update(float deltaTime) override;
    /// Getter
    // Box Collider Data
    void SetHeight(float h) { Height = h; Scala.x = Width/2; Scala.y = -Height/2; };
    /// Setter
    void SetWidth(float w) { Width = w; Scala.x = Width/2; Scala.y = -Height/2; };

    bool CheckCrash(BoxCollider& other);
    bool CheckCrash(class LineCollider& other);
    Vector2 FixObjectPos(Collider& other);
    Vector2 FixObjectPos(BoxCollider& other);
    Vector2 FixObjectPos(class LineCollider& other);

    Vector2 MinPos;
    Vector2 MaxPos;
    Vector2 MidTopPos;
    Vector2 MidBottomPos;

private:
    //Box Collider Data
    Vector2 Center;
    Vector2 Scala;
    float Width = 100;
    float Height = 100;
};
