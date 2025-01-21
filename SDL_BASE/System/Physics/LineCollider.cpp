//
// Created by binetsu on 9/14/24.
//

#include "LineCollider.h"
#include "System/GameObject/GameObject.h"
#include "System/Process/Processer.h"
#include "System/Process/PhysicsProcesser.h"

#ifdef _DEBUG
#include "System/Utility/DebugRay.h"
#endif

LineCollider::LineCollider(class GameObject *owner, int updateOrder)
        :Collider(owner,updateOrder),
        posA(0,0),
        posB(0,0)
        {
            SetColliderType(LineCol);
            mOwner = owner;

#ifdef _DEBUG
            ColliderRay = new DebugRay();
            MaxPosRay = new DebugRay();
            auto color = new RayColor(0,255,0,255);
            auto Rcolor = new RayColor(255,0,0,255);
            ColliderRay->CreateLineRayObject(
                    &posA,
                    &posB,
                    color);

            MaxPosRay->CreateRayObject(Center.x-5,Center.y-5,10,10,color);
#endif

            Center.x = mOwner->GetPosition().x;
            Center.y = mOwner->GetPosition().y;

            posA.y = posA.y*-1;
            posB.y = posB.y*-1;
            posA += Center;
            posB += Center;

            Singleton<PhysicsProcesser>::GetInstance().AddCollider(this);
        }

bool LineCollider::UpdateColliderData() {

    Center.x = mOwner->GetPosition().x;
    Center.y = mOwner->GetPosition().y;

    return true;
}

void LineCollider::Update(float deltaTime) {
#ifdef _DEBUG
    ColliderRay->UpdateLineRayObject(&posA,&posB);
    MaxPosRay->UpdateRayObject(Center.x-5,Center.y-5,10,10);
#endif

}
bool LineCollider::CheckCrash(Collider& other) {
    return false;
}
bool LineCollider::CheckCrash(LineCollider& other) {

    if(CheckLineToLineCrash(other.posA,other.posB,posA,posB)){
        AddCrashedCollider(other);
        return true;
    }
    DeleteCrashedCollider(other);
    return false;
}

Vector2 LineCollider::FixObjectPos(Collider& other) {
    return Vector2::Zero;
}


LineCollider::~LineCollider() {
    Singleton<PhysicsProcesser>::GetInstance().DeleteCollider(this);
}