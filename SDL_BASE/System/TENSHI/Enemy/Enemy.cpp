
#include "Enemy.h"
#include "System/Component/AnimSpriteComponent.h"
#include "System/Process/Processer.h"
#include "System/Process/AssetLoader.h"
#include "System/Process/InputReader.h"
#include "System/Process/Renderer.h"
#include "System/Data/AssetPath.h"
#include "System/Component/FSM/StateMachine.h"
#include "System/Physics/Rigidbody.h"
#include "System/Physics/Collider.h"
#include "System/Physics/BoxCollider.h"
#include "System/Process/PhysicsProcesser.h"
#include "System/RayCast/RayCastObject.h"
#include "spdlog/spdlog.h"
#include "EnemyIdleState.h"
#include "System/TENSHI/Damage/Health.h"
#include "EnemyManager.h"

#ifdef _DEBUG
#include "System/Utility/DebugRay.h"
#endif

Enemy::Enemy(Vector2 pos,MonsterData* data,EnemyData* mdata,EnemyManager* manager)
	:GameObject(pos),
    enemyData(data),
    mEnemyData(mdata),
    mManager(manager)
{
    GameObjectName = "Enemy";
    mStateMachine = new StateMachine(this);
    mRigidBody = new Rigidbody(this);
    mCollider = new BoxCollider(this);
    mHealth = new Health(this,30);
    mCollider->SetColliderLayer(ColliderLayer::L_Enemy);
    mCollider->SetHeight(data->Monster_Height);
    mCollider->SetWidth(data->Monster_Width);
    mCollider->UpdateColliderData();

    GroundRayCast = new LineCollider(this);
    GroundRayCast->OnlyTrigger = true;
    mCollider->OnlyTrigger = true;

    GroundRayCast->SetColliderLayer(ColliderLayer::L_Ground);

    mCollider->SetRigid(*mRigidBody);
    mRigidBody->SetmCollider(*mCollider);

    mAnimSpriteComponent = new AnimSpriteComponent(this,99);
    //mAnimSpriteComponent = GetComponent<AnimSpriteComponent>();
    auto* idlestate = new EnemyIdleState(this,mStateMachine);
    mStateMachine->SetStartState(idlestate);
    SetRayCastData();
    UpdateRayCastPosition();
#ifdef _DEBUG
    RayCastRay = new DebugRay();
    RayCastRay->CreateLineRayObject(&GroundLineColP1,
                                    &GroundLineColP1,Bcolor);
    WallRayCastRay = new DebugRay();
    WallRayCastRay->CreateLineRayObject(&WallRayCastP1,
                                    &mPosition,Rcolor);
#endif

}

void Enemy::SetRayCastData() {
    GroundLineColP1 = Vector2(0,(GetHeight()+15/2)-20);
    GroundLineColP2 = Vector2(0,(GetHeight()+15)/2);
    GroundRayCastP1Vel = Vector2(0,10);
    GroundRayCastP2Vel = Vector2(0,(GetHeight())/2);
    WallRayCastP1Vel = Vector2((GetWidth()+20)/2,0);
    WallRayCastP2Vel = Vector2(-(GetWidth()+20)/2,0);
}

void Enemy::UpdateRayCastPosition() {
    GroundRayCastP1 = mPosition+GroundRayCastP1Vel;
    GroundRayCastP2 = mPosition+GroundRayCastP2Vel;
    WallRayCastP1 = mPosition+WallRayCastP1Vel;
    WallRayCastP2 = mPosition+WallRayCastP2Vel;
}
void Enemy::UpdateObject(float deltaTime)
{
    UpdateRayCastPosition();
    GameObject::UpdateObject(deltaTime);

    //X +45 Y -30
    // Ground Check
    GroundRayCast->SetPosA(&GroundLineColP1);
    GroundRayCast->SetPosB(&GroundLineColP2);

    Isground = RayCastObject::RayCast(&GroundRayCastP1,
                                      &GroundRayCastP2);
#ifdef _DEBUG
    RayCastRay->UpdateLineRayObject(&GroundRayCastP1,
                                    &GroundRayCastP2);
#endif

    if(Flip){
        auto Result= RayCastObject::RayCastReturn(&WallRayCastP1,
                                        &mPosition);
        if(Result!= nullptr){
            if(Result->posA.x==Result->posB.x)
                IsWall = true;
        }else{
            IsWall= false;
        }
#ifdef _DEBUG
        WallRayCastRay->UpdateLineRayObject(&WallRayCastP1,
                                            &mPosition);
#endif
    }else{

        auto Result = RayCastObject::RayCastReturn(&WallRayCastP2,
                                        &mPosition);
        if(Result!= nullptr){
            if(Result->posA.x==Result->posB.x)
                IsWall = true;
        }else{
            IsWall= false;
        }
#ifdef _DEBUG
        WallRayCastRay->UpdateLineRayObject(&WallRayCastP2,
                                            &mPosition);
#endif
    }

    GroundRayCast->UpdateColliderData();

}

void Enemy::OnTriggerEnter(Collider& other) {

    GameObject::OnTriggerEnter(other);

    if(other.GetColliderLayer()==ColliderLayer::L_Ground){
        CurrentGround = &other;
    }
}

void Enemy::OnTriggerStayEnter(Collider& other) {
    GameObject::OnTriggerStayEnter(other);

    if(other.GetColliderLayer()==ColliderLayer::L_Ground){
        CurrentGround = &other;
    }
}

void Enemy::OnTriggerExit(Collider& other) {
    GameObject::OnTriggerExit(other);
    if(other.GetColliderLayer()==ColliderLayer::L_Ground){
        Isground = false;
        CurrentGround = nullptr;
    }
}

void Enemy::OnColliderEnter(class Collider& other) {}

void Enemy::OnColliderExit(class Collider& others) {}

Enemy::~Enemy(){
    mManager->OnEnemyDead(mEnemyData);
#ifdef _DEBUG
    delete RayCastRay;
    delete WallRayCastRay;
#endif
}

