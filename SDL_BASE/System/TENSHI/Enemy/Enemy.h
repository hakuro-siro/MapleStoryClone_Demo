
#pragma once
#include "System/GameObject/GameObject.h"
#include "System/TENSHI/Player/Skill/Skill.h"
#include "System/Data/MonsterData.h"
#include "System/Data/EnemyData.h"

class Enemy : public GameObject
{
public:
    Enemy(Vector2 pos,MonsterData* data,EnemyData* mdata,class EnemyManager* manager);
    ~Enemy();
	void UpdateObject(float deltaTime) override;
    /// Getter
    class Rigidbody* GetRigid() const { return  mRigidBody; }
    class BoxCollider* GetCollider() const {return mCollider;}
    class AnimSpriteComponent* GetAnimSpriteComponent() const {return mAnimSpriteComponent;};

    void OnTriggerStayEnter(class Collider& other)override;
    void OnTriggerEnter(class Collider& other) override;
    void OnColliderEnter(class Collider& other) override;
    void OnTriggerExit(class Collider& other) override;
    void OnColliderExit(class Collider& others) override;
    void UpdateRayCastPosition();

    std::unordered_map<string,Skill*> PlayerSkills;

    bool Isground = false;
    bool IsWall = false;

    Vector2 GroundLineColP1 = Vector2::Zero;
    Vector2 GroundLineColP2 = Vector2::Zero;
    Vector2 GroundRayCastP1Vel = Vector2::Zero;
    Vector2 GroundRayCastP2Vel = Vector2::Zero;
    Vector2 WallRayCastP1Vel = Vector2::Zero;
    Vector2 WallRayCastP2Vel = Vector2::Zero;

    Vector2 GroundRayCastP1 = Vector2::Zero;
    Vector2 GroundRayCastP2 = Vector2::Zero;
    Vector2 WallRayCastP1 = Vector2::Zero;
    Vector2 WallRayCastP2 = Vector2::Zero;

    MonsterData* enemyData = nullptr;
    EnemyData* mEnemyData = nullptr;
    class EnemyManager* mManager = nullptr;

    class Health* GetHealth() { return mHealth; }
private:
    void SetRayCastData();
    class BoxCollider* mCollider = nullptr;
    class LineCollider* GroundRayCast = nullptr;
    class StateMachine* mStateMachine = nullptr;
    class AnimSpriteComponent* mAnimSpriteComponent = nullptr;
    class Rigidbody* mRigidBody = nullptr;
    class Health* mHealth = nullptr;
#ifdef _DEBUG
    class DebugRay* RayCastRay = nullptr;
    class DebugRay* WallRayCastRay = nullptr;
#endif
};