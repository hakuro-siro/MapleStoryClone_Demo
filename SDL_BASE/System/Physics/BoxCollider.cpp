//
// Created by binetsu on 9/11/24.
//

#include "System/GameObject/GameObject.h"
#include "System/Process/Processer.h"
#include "System/Process/PhysicsProcesser.h"

#include "BoxCollider.h"
#include "Rigidbody.h"
#include "LineCollider.h"

#include "algorithm"
#include <iostream>

#ifdef _DEBUG
#include "System/Utility/DebugRay.h"
#endif
BoxCollider::BoxCollider(class GameObject* owner, int updateOrder,SDL_Rect* rect)
        : Collider(owner,updateOrder,rect),
        MinPos(Vector2::Zero),
        MaxPos(Vector2::Zero)
        {
            SetColliderType(BoxCol);
            mOwner = owner;

            if(ColliderRect!= nullptr)
            {
                Center.x = ColliderRect->x;
                Center.y = ColliderRect->y+ColliderRect->h/2;
                Scala.x = ColliderRect->w/2;
                Scala.y = -ColliderRect->h/2;
            }
            else
            {
                Center.x = mOwner->GetPosition().x;
                Center.y = mOwner->GetPosition().y;
                Scala.x = Width/2;
                Scala.y = -Height/2;
            }

#ifdef _DEBUG
            ColliderRay = new DebugRay();
            ColliderRay->CreateRayObject(Center.x,Center.y,Width,Height,Gcolor);
            MaxPosRay = new DebugRay();
#endif

            Singleton<PhysicsProcesser>::GetInstance().AddCollider(this);

        }


bool BoxCollider::UpdateColliderData() {
    if(ColliderRect!= nullptr)
    {
        Center.x = ColliderRect->x+ColliderRect->w/2;
        Center.y = ColliderRect->y+ColliderRect->h/2;
    }
    else
    {
        Center.x = mOwner->GetPosition().x;
        Center.y = mOwner->GetPosition().y;
    }

    MinPos = Center - Scala;
    MaxPos = Center + Scala;
    MidBottomPos = Center - Vector2(0,Scala.y);
    MidTopPos = Center + Vector2(0,Scala.y);
    return true;
}

void BoxCollider::Update(float deltaTime) {
#ifdef _DEBUG
    ColliderRay->UpdateRayObject(Center.x - Width/2,Center.y-Height/2,Width,Height);
#endif
}


bool BoxCollider::CheckCrash(BoxCollider& other) {
    /// 임시
    bool outside = Collider::CheckBoxToBoxCrash(MaxPos,MinPos,other.MaxPos,other.MinPos);

    if(!outside) {
        AddCrashedCollider(other);
    } else{
        DeleteCrashedCollider(other);
    }

    return !outside;
}
bool BoxCollider::CheckCrash(LineCollider& other) {
   Vector2 MaxX_MinY = Vector2{MaxPos.x,MinPos.y};
    Vector2 MinX_MaxY = Vector2{MinPos.x,MaxPos.y};

    if(other.posA.y==other.posB.y) {
        if(Collider::CheckLineToLineCrash(other.posA,other.posB,MidBottomPos,MidTopPos)){
            AddCrashedCollider(other);
            return true;
        }
    }
    // Vertical Line
    if(other.posA.x==other.posB.x){
        if(Collider::CheckLineToLineCrash(other.posA,other.posB,MaxPos,MinX_MaxY))
        {
            AddCrashedCollider(other);
            return true;
        }
        if(Collider::CheckLineToLineCrash(other.posA,other.posB, MinPos,MaxX_MinY)){
            AddCrashedCollider(other);
            return true;
        }
    }
    // Common Case
    if(Collider::CheckLineToLineCrash(other.posA,other.posB,MidBottomPos,Center)){
        AddCrashedCollider(other);
        return true;
    }
    DeleteCrashedCollider(other);
    return false;
}

Vector2 BoxCollider::FixObjectPos(Collider& other) {
    Vector2 vec = Vector2::Zero;
    Vector2 FixedVector = Vector2::Zero;

    switch (other.GetColliderType()) {
        BoxCollider* box;
        case ColliderType::BoxCol:
            box = dynamic_cast<BoxCollider*>(&other);
            vec = FixObjectPos(*box);
            if(vec.x!=0||vec.y!=0){
                if(FixedVector.x==0)
                    FixedVector.x+=vec.x;
                if(FixedVector.y==0)
                    FixedVector.y+=vec.y;
            }
            break;
        LineCollider* dia;
        case ColliderType::LineCol:
            dia = dynamic_cast<LineCollider*>(&other);
            vec = FixObjectPos(*dia);
            if(vec.x!=0||vec.y!=0){
                if(FixedVector.x==0)
                    FixedVector.x += vec.x;
                if(FixedVector.y==0)
                    FixedVector.y+=vec.y;
            }
            break;
    }
    //SPDLOG_INFO("FiXED VECTOR {}/{} ",FixedVector.x,FixedVector.y);
    if(FixedVector.x!=0||FixedVector.y!=0){
        Vector2 Pos = mOwner->GetPosition();
        Pos += FixedVector;
        mOwner->SetPosition(Pos);

    }
    return FixedVector;
}

Vector2 BoxCollider::FixObjectPos(BoxCollider& other) {

    Vector2 pos = Vector2::Zero;
    float dx1 = this->MinPos.x - other.MaxPos.x;
    float dx2 = this->MaxPos.x - other.MinPos.x;
    float dy1 = this->MinPos.y - other.MaxPos.y;
    float dy2 = this->MaxPos.y - other.MinPos.y;

    float dx = (Math::Abs(dx1)< Math::Abs(dx2)?dx1:dx2);
    float dy = (Math::Abs(dy1)< Math::Abs(dy2)?dy1:dy2);

    if(Math::Abs(dx) <= Math::Abs(dy)){
        pos.x -= dx;

    }
    else
    {
        pos.y -=dy;

    }
    if(other.OnlyTrigger||this->OnlyTrigger)
        return Vector2::Zero;
    return pos;
}

Vector2 BoxCollider::FixObjectPos(LineCollider& other) {
    if(!Active)
    {
        return Vector2::Zero;
    }

    std::vector<Vector2> RectCorners = {
        MidBottomPos,
        Center,
        Vector2{MaxPos.x,MinPos.y},
        Vector2{MinPos.x,MaxPos.y}};
    Vector2 MiniVector = MidBottomPos + Vector2(0,+5);

    std::vector<Vector2> vectors;

    if(Collider::Collider::CheckLineToLineCrash(other.posA,other.posB,RectCorners[0],RectCorners[1])){

        if(other.posA.y!=other.posB.y) {

            auto FixedVector = CalculateLineToLineDistance(
                        other.posA,
                        other.posB,
                        RectCorners[0],
                        RectCorners[1]);
                if (other.posA.y > other.posB.y) {
                    if (FixedVector.x < 0)
                        FixedVector.x = 0;

                    vectors.push_back(FixedVector);
                } else {
                    if (FixedVector.x > 0)
                        FixedVector.x = 0;
                    vectors.push_back(FixedVector);
            }
        }
        else
        {
            if(other.posA.y<MidBottomPos.y)
            {
                    Vector2 vec = Vector2(
                    0,
                    CalculateLineToLineDistance(other.posA,other.posB,RectCorners[0],RectCorners[1]).y);
                    vectors.push_back(vec);
            }
        }
    }

    if(other.posA.x==other.posB.x) {
        if (Collider::CheckLineToLineCrash(other.posA, other.posB, MaxPos,RectCorners[3])) {
            vectors.push_back(
                    CalculateLineToLineDistance(other.posA, other.posB,MaxPos, RectCorners[3]));
        }
        if (Collider::CheckLineToLineCrash(other.posA, other.posB, MinPos,RectCorners[2])) {
            vectors.push_back(
                    CalculateLineToLineDistance(other.posA, other.posB,MinPos, RectCorners[2]));
        }
    }

    Vector2 Min = Vector2::Zero;

    float Minlen = std::numeric_limits<float>::max();
    float Len = 0.0f;

    for(auto& vec : vectors){
        Len = vec.Length();
        if(Len!=0){
            if(Len < Minlen){
                Min = vec;
                Minlen = Len;
            }
        }
    }

    //Vector2 Pos = mOwner->GetPosition();

    Min.x = -Min.x;
    Min.y = -Min.y;
    //SDL_Log("%f / %f",Min.x,Min.y);
    if(Min.y>0){
        Min.y=0;
    }
    //Pos += Min;

    //mOwner->SetPosition(Pos);

    //return Vector2::Zero;
    if(other.OnlyTrigger)
        return Vector2::Zero;
    return Min;
}

BoxCollider::~BoxCollider() {
    Singleton<PhysicsProcesser>::GetInstance().DeleteCollider(this);
}