//
// Created by binetsu on 9/14/24.
//

#include "System/GameObject/GameObject.h"
#include "System/Process/Processer.h"
#include "System/Process/PhysicsProcesser.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "LineCollider.h"

#ifdef _DEBUG
#include "System/Utility/DebugRay.h"
#endif
/// Constructor
Collider::Collider(class GameObject* owner, int updateOrder, SDL_Rect* rect) :
        Component(owner,updateOrder),
        Rigidbody(nullptr),
        ColliderRect(rect)
{
}

void Collider::OnTriggerStayEnter(Collider& other) { mOwner->OnTriggerStayEnter(other); }
void Collider::OnColliderEnter(Collider& other) { mOwner->OnColliderEnter(other); }
void Collider::OnColliderExit(Collider& other) { mOwner->OnColliderExit(other); }
void Collider::OnTriggerEnter(Collider& other) { mOwner->OnTriggerEnter(other); }
void Collider::OnTriggerExit(Collider& other) { mOwner->OnTriggerExit(other); }


/// Check Crash
/// Common Crash
bool Collider::CheckCrash(class Collider &other) {
    return false;
}

/// IsGround 업데이트 용
/// CrashTest 결과가 true 인 Collider가 하나라도 있다면 플래그 올리기
/// TDL :  가로 충돌시 플래그 올라가는지 체크
void Collider::UpdateCrashFlag()
{
}

/// Crash 이후 위치 보정용
Vector2 Collider::FixObjectPos(Collider& other) {
    switch (this->GetColliderType()) {
        case ColliderType::BoxCol:
            return dynamic_cast<BoxCollider*>(this)->FixObjectPos(other);
            break;
        case ColliderType::LineCol:
            return dynamic_cast<LineCollider*>(this)->FixObjectPos(other);
            break;
    }
    return Vector2::Zero;
}


void Collider::Update(float deltaTime) {

}
void Collider::AddCrashedCollider(Collider& col) {
    if(std::find(CrashedColliders.begin(),CrashedColliders.end(),&col) == CrashedColliders.end())
    {
        //SPDLOG_INFO("AddCrashedCollider");
        CrashedColliders.emplace_back(&col);
        if(OnlyTrigger){
            if(col.Layer==Layer) {
                OnTriggerEnter(col);
            }
        }
        else{
            if(col.OnlyTrigger)
            {
                col.OnTriggerEnter(*this);
            }
            OnColliderEnter(col);
        }
    }
    else
    {
        if(OnlyTrigger) {
            if(col.Layer==Layer) {
                OnTriggerStayEnter(col);
            }
        }else{
            if(col.OnlyTrigger)
            {
                col.OnTriggerStayEnter(*this);
            }
        }
    }
}
void Collider::DeleteCrashedCollider(Collider& col)
{
    if(std::find(CrashedColliders.begin(),CrashedColliders.end(),&col) != CrashedColliders.end())
    {
        auto iter = std::find(CrashedColliders.begin(), CrashedColliders.end(), &col);
        CrashedColliders.erase(iter);

        if(OnlyTrigger){
            OnTriggerExit(col);
        }
        else{
            if(col.OnlyTrigger)
            {
                col.OnTriggerExit(*this);
            }
            OnColliderExit(col);
        }
    }
}

bool Collider::CheckBoxToBoxCrash(Vector2& MaxPos,Vector2& MinPos, Vector2& MaxPos2,Vector2& MinPos2) {

    bool outside =
            MaxPos.x < MinPos2.x||
            -MaxPos.y <= -MinPos2.y||
            MaxPos2.x < MinPos.x||
            -MaxPos.y <= -MinPos2.y;

    return outside;
}

bool Collider::CheckLineToLineCrash(Vector2 &Line1_P1, Vector2 &Line1_P2, Vector2 &Line2_P1, Vector2 &Line2_P2) {
    auto Orientation =
            [](const Vector2& a, const Vector2& b,const Vector2& c) -> int
            {
                float val = (b.y - a.y)*(c.x-b.x)-(b.x-a.x)*(c.y-b.y);
                if(val == 0)
                    return 0;
                return (val>0)?1:2;
            };

    int o1 = Orientation(Line1_P1,Line1_P2,Line2_P1);
    int o2 = Orientation(Line1_P1,Line1_P2,Line2_P2);
    int o3 = Orientation(Line2_P1,Line2_P2,Line1_P1);
    int o4 = Orientation(Line2_P1,Line2_P2,Line1_P2);

    if(o1!=o2&&o3!=o4)
        return true;
    else
        return false;
}
Vector2 Collider::CalculateLineToLineDistance(
        Vector2 &Line1_P1,
        Vector2 &Line1_P2,
        Vector2 &Line2_P1,
        Vector2 &Line2_P2)
{
    std::vector<Vector2> vectors;

    vectors.push_back(CalculatePointToLineDistance(Line1_P1,Line2_P1,Line2_P2));
    vectors.push_back(CalculatePointToLineDistance(Line1_P2,Line2_P1,Line2_P2));
    vectors.push_back(CalculatePointToLineDistance(Line2_P1,Line1_P1,Line1_P2));
    vectors.push_back(CalculatePointToLineDistance(Line2_P2,Line1_P1,Line1_P2));

    Vector2 Min = Vector2::Zero;

    float Minlen = std::numeric_limits<float>::max();
    float Len = 0;

    for(auto& vec : vectors){
        Len = vec.Length();
        if(Len < Minlen){
            Min = vec;
            Minlen = Len;
        }
    }
    return Min;

}

Vector2 Collider::CalculatePointToLineDistance(Vector2 &p1, Vector2 &q1, Vector2 &q2) {
    Vector2 Q1Q2 = q2-q1; //b -a
    Vector2 Q1P1 = p1-q1; // p -a
    float T = Q1P1.Dot(Q1P1,Q1Q2)/Q1Q2.Dot(Q1Q2,Q1Q2);
    if(T<0.0f)
        return (p1-q1);
    if(T>1.0f)
        return (p1-q2);
    Vector2 Projection = q1 + Q1Q2 * T;
    return (p1-Projection);
}

Collider::~Collider(){
#ifdef _DEBUG
    delete MaxPosRay;
    delete ColliderRay;
#endif
}