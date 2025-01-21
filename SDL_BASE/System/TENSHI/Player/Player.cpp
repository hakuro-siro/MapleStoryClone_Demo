
#include "Player.h"
#include "System/Component/AnimSpriteComponent.h"
#include "System/Process/Processer.h"
#include "System/Process/AssetLoader.h"
#include "System/Process/InputReader.h"
#include "System/Process/Renderer.h"
#include "PlayerMoveState.h"
#include "System/Data/AssetPath.h"
#include "System/Component/FSM/StateMachine.h"
#include "PlayerIdleState.h"
#include "System/Physics/Rigidbody.h"
#include "System/Physics/Collider.h"
#include "System/Physics/BoxCollider.h"
#include "System/Process/PhysicsProcesser.h"
#include "System/RayCast/RayCastObject.h"
#include "spdlog/spdlog.h"
#include "System/TENSHI/Damage/Health.h"

#ifdef _DEBUG
#include "System/Utility/DebugRay.h"
#endif

Player::Player(Vector2 pos)
	:GameObject(pos)
{
    mStateMachine = new StateMachine(this);
    mRigidBody = new Rigidbody(this);
    mCollider = new BoxCollider(this);
    mHealth = new Health(this,500);
    mCollider->SetHeight(73);
    mCollider->SetWidth(64);
    mCollider->SetColliderLayer(ColliderLayer::L_Player);
    mCollider->UpdateColliderData();

    GroundRayCast = new LineCollider(this);
    GroundRayCast->OnlyTrigger = true;

    GroundRayCast->SetColliderLayer(ColliderLayer::L_Ground);

    SubscribeInputEvent();

    Singleton<Renderer>::GetInstance().MainCamera->GetComponent<Camera>()->FollowThis(this);
    mCollider->SetRigid(*mRigidBody);
    mRigidBody->SetmCollider(*mCollider);

    mAnimSpriteComponent = new AnimSpriteComponent(this);
    //mAnimSpriteComponent = GetComponent<AnimSpriteComponent>();
    auto* idlestate = new PlayerIdleState(this,mStateMachine);
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
void Player::SetRayCastData() {
    GroundLineColP1 = Vector2(0,10);
    GroundLineColP2 = Vector2(0,(GetHeight()+50)/2);
    GroundRayCastP1Vel = Vector2(0,10);
    GroundRayCastP2Vel = Vector2(0,(GetHeight()+50)/2);
    WallRayCastP1Vel = Vector2((GetWidth()+20)/2,0);
    WallRayCastP2Vel = Vector2(-(GetWidth()+20)/2,0);
}

void Player::UpdateRayCastPosition() {
    GroundRayCastP1 = mPosition+GroundRayCastP1Vel;
    GroundRayCastP2 = mPosition+GroundRayCastP2Vel;
    WallRayCastP1 = mPosition+WallRayCastP1Vel;
    WallRayCastP2 = mPosition+WallRayCastP2Vel;
}
void Player::UpdateObject(float deltaTime)
{
    if(Singleton<Processer>::GetInstance().SceneMoving){
        CurrentGround= nullptr;
        return;
    }
    if( Singleton<Renderer>::GetInstance().MainCamera->GetComponent<Camera>()->Target== nullptr){
        Singleton<Renderer>::GetInstance().MainCamera->GetComponent<Camera>()->FollowThis(this);

    }
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

void Player::SubscribeInputEvent()
{

}

void Player::OnTriggerEnter(Collider& other) {

    GameObject::OnTriggerEnter(other);

    if(other.GetColliderLayer()==ColliderLayer::L_Ground){
        auto Ground = dynamic_cast<LineCollider*>(&other);
        //SPDLOG_INFO("{}//{}",mPosition.x,mPosition.y);
        //SPDLOG_INFO("{}/{}",Ground->posA.y,Ground->posB.y);

        CurrentGround = &other;
    }
}

void Player::OnTriggerStayEnter(Collider& other) {
    GameObject::OnTriggerStayEnter(other);

    if(other.GetColliderLayer()==ColliderLayer::L_Ground){
        CurrentGround = &other;
    }
}

void Player::OnTriggerExit(Collider& other) {
    GameObject::OnTriggerExit(other);
    if(other.GetColliderLayer()==ColliderLayer::L_Ground){
        Isground = false;
        CurrentGround = nullptr;
    }
}

void Player::OnColliderEnter(class Collider& other) {}

void Player::OnColliderExit(class Collider& others) {}

Player::~Player(){
#ifdef _DEBUG
    delete RayCastRay;
    delete WallRayCastRay;
#endif
    Singleton<Renderer>::GetInstance().MainCamera->GetComponent<Camera>()->ForgetMe();
}

