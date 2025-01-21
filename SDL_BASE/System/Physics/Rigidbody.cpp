//
// Created by binetsu on 9/10/24.
//

#include "Rigidbody.h"
#include "System/GameObject/GameObject.h"
#include "Collider.h"
#include "System/Process/PhysicsProcesser.h"
#include "System/Process/Processer.h"
#include "System/RayCast/RayCastObject.h"
#include <iostream>

Rigidbody::Rigidbody(class GameObject* owner, int updateOrder) :
        Component(owner,updateOrder)
        {
    GravityVector = new Vector2(0,-Gravity);
}

void Rigidbody::Update(float deltaTime) {
    if(!CheckGround())
    {
        if(AddForceVector.y==0)
             UpdateGravity(deltaTime);
    }
    else{
        RigidVector = Vector2::Zero;
    }

    UpdatePhysics(deltaTime);
    mCollider->UpdateColliderData();
}

bool Rigidbody::CheckGround() {
    CheckGroundAPos1.x = mOwner->GetPosition().x;
    //CheckGroundAPos1.y = mOwner->GetPosition().y-(mOwner->GetHeight()/2);
    CheckGroundAPos1.y = mOwner->GetPosition().y;
    CheckGroundAPos2.x = mOwner->GetPosition().x;
    CheckGroundAPos2.y = mOwner->GetPosition().y+(mOwner->GetHeight()/2)+5;

    CheckGroundBPos1.x = mOwner->GetPosition().x;
    CheckGroundBPos1.y = mOwner->GetPosition().y;
    CheckGroundBPos2.x = mOwner->GetPosition().x;
    CheckGroundBPos2.y = mOwner->GetPosition().y-(mOwner->GetHeight()/2);
//
//    CheckGroundCPos1.x = mOwner->GetPosition().x+(mOwner->GetWidth()/2);
//    CheckGroundCPos1.y = mOwner->GetPosition().y+(mOwner->GetHeight()/2)-10;
//    CheckGroundCPos2.x = mOwner->GetPosition().x+(mOwner->GetWidth()/2);
//    CheckGroundCPos2.y = mOwner->GetPosition().y+(mOwner->GetHeight()/2)+5;
//

    return
    RayCastObject::RayCast(&CheckGroundAPos1,&CheckGroundAPos2)
 &&!RayCastObject::RayCast(&CheckGroundBPos1,&CheckGroundBPos2);
//    RayCastObject::RayCast(&CheckGroundCPos1,&CheckGroundCPos2);

}
void Rigidbody::UpdatePhysics(float deltaTime) {
        CalculateForce(deltaTime);
        Vector2 DesirePosition = mOwner->GetPosition();
        //SPDLOG_INFO("Force : {} / {}",Force.x,Force.y);
        DesirePosition += Force * deltaTime;
        DesirePosition += AddForceVector;
        mOwner->SetPosition(DesirePosition);
        mCollider->UpdateColliderData();
}
void Rigidbody::AddForce(Vector2 ForceVector) {
    AddForceVector = ForceVector;

}

void Rigidbody::UpdateGravity(float deltaTime) {
    RigidVector += *GravityVector;
    if(RigidVector.y>GravityForceLimit){
        RigidVector.y = GravityForceLimit;
    }
}

void Rigidbody::CalculateForce(float deltaTime) {
    Force = RigidVector * Mass;
}

Rigidbody::~Rigidbody() noexcept {

}