//
// Created by binetsu on 9/14/24.
//

#include "System/Component/Component.h"
#include "System/Utility/Math.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "SDL2/SDL.h"
#pragma once

enum ColliderType {
    BoxCol = 0,
    LineCol = 1,
    NoCol = 9999
};
const std::unordered_map<std::string,ColliderType> ColliderMap{
        {"BoxCol",ColliderType::BoxCol},
        {"LineCol",ColliderType::LineCol}
};

enum ColliderLayer {
    L_Enemy = 0,
    L_Ground = 1,
    L_Wall = 2,
    L_Common = 3,
    L_Player = 999
};

class Collider : public Component{
public:

    Collider(class GameObject* owner, int updateOrder = 100, SDL_Rect* rect = nullptr);
    ~Collider();
    void Update(float deltaTime) override;

    virtual void OnTriggerStayEnter(class Collider& other);
    virtual void OnTriggerEnter(class Collider& other);
    virtual void OnColliderEnter(class Collider& other);
    virtual void OnTriggerExit(class Collider& other);
    virtual void OnColliderExit(class Collider& others);


    virtual bool UpdateColliderData() = 0;
    void UpdateCrashFlag();
    virtual bool CheckCrash(class Collider& other);
    virtual Vector2 FixObjectPos(class Collider& other);
    //virtual Vector2 FixObjectPos(class BoxCollider* other);


    static bool CheckBoxToBoxCrash(Vector2& MaxPos, Vector2& MinPos, Vector2& MaxPos2, Vector2& MinPos2);
    static bool CheckLineToLineCrash(Vector2& Line1_P1, Vector2& Line1_P2, Vector2& Line2_P1, Vector2& Line2_P2);
    Vector2 CalculatePointToLineDistance(Vector2& p1,Vector2& q1, Vector2& q2);
    Vector2 CalculateLineToLineDistance(Vector2& Line1_P1,Vector2& Line1_P2,Vector2& Line2_P1, Vector2& Line2_P2);


    void AddCrashedCollider(Collider& col);
    void DeleteCrashedCollider(Collider& col);
    /// Getter - Setter
    void SetColliderType(ColliderType type) { Type = type; }
    void SetColliderLayer(ColliderLayer layer) { Layer = layer; }

    void SetRigid(class Rigidbody& rigidbody) { Rigidbody = &rigidbody;}

    ColliderType GetColliderType() const { return Type;}
    ColliderLayer GetColliderLayer() const  { return Layer;}
    class Rigidbody* GetRigidbody() const { return  Rigidbody;}


    std::vector<Collider*> CrashedColliders;
    bool OnlyTrigger = false;
    bool Active = true;
protected:
    SDL_Rect* ColliderRect = nullptr;
    class Rigidbody* Rigidbody = nullptr;
#ifdef _DEBUG
    class DebugRay* ColliderRay = nullptr;
    class DebugRay* MaxPosRay = nullptr;
#endif
private:
    ColliderType Type = ColliderType::NoCol;
    ColliderLayer Layer = ColliderLayer::L_Common;
};
