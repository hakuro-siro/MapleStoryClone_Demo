//
// Created by binetsu on 11/5/24.
//

#include "RayCastObject.h"
#include "System/Utility/Singleton.h"
#include "System/Process/PhysicsProcesser.h"
#include "System/GameObject/GameObject.h"

RayCastObject::RayCastObject(GameObject *owner, int updateOrder, SDL_Rect *rect):
        Component(owner)
{

}

void RayCastObject::Update(float deltaTime) {

}

bool RayCastObject::RayCast(Vector2* StartPosition, Vector2* EndPosition) {
    auto Colliders = Singleton<PhysicsProcesser>::GetInstance().GetLineCollider();
    for(auto& col : Colliders){
        if(Collider::CheckLineToLineCrash(*StartPosition,*EndPosition,col->posA,col->posB))
        {
            return true;
        }
    }
    return false;
}
bool RayCastObject::BoxRayCast(Vector2* MinPosition, Vector2* MaxPosition)
{
    auto Colliders = Singleton<PhysicsProcesser>::GetInstance().GetBoxCollider();
    for(auto& col : Colliders){
        if(!Collider::CheckBoxToBoxCrash(
                *MinPosition,*MaxPosition,col->MinPos,col->MaxPos))
        {
            return true;
        }
    }
    return false;
}
vector<GameObject*> RayCastObject::BoxRayCastReturn(Vector2* MinPosition, Vector2* MaxPosition,ColliderLayer CastLayer)
{
    auto Colliders = Singleton<PhysicsProcesser>::GetInstance().GetBoxCollider();
    vector<GameObject*> CastReturn;
    for(auto& col : Colliders){
        if(!Collider::CheckBoxToBoxCrash(
                *MaxPosition,*MinPosition,col->MaxPos,col->MinPos))
        {
            if(col->GetColliderLayer()==CastLayer)
                CastReturn.emplace_back(col->GetOwner());
        }
    }
    return CastReturn;
}
LineCollider* RayCastObject::RayCastReturn(Vector2* StartPosition, Vector2* EndPosition) {
    auto Colliders = Singleton<PhysicsProcesser>::GetInstance().GetLineCollider();
    for(auto& col : Colliders){
        if(Collider::CheckLineToLineCrash(*StartPosition,*EndPosition,col->posA,col->posB))
        {
            return col;
        }
    }
    return nullptr;
}

RayCastObject::~RayCastObject() noexcept {

}
