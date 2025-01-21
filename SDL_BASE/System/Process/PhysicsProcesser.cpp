//
//
// Created by binetsu on 9/10/24.
//

#include "PhysicsProcesser.h"
#include "System/GameObject/GameObject.h"
#include "System/Physics/Rigidbody.h"
#include "Processer.h"
#include <algorithm>
#include <iostream>

PhysicsProcesser::PhysicsProcesser() {
}

bool PhysicsProcesser::Initialize() {

    IProcess::Initialize();

    Bind_Processer = true;
    return true;
}

void PhysicsProcesser::Update(float deltaTime) {
    UpdatePhysics(deltaTime);
}


void PhysicsProcesser::UpdatePhysics(float deltaTime) {

    CheckCrash();

    //SPDLOG_INFO("FixPosCollider {}",FixPosColliders.size());
    for(auto& collider : FixPosColliders)
    {
        for(auto& other : collider->CrashedColliders)
        {
            collider->FixObjectPos(*other);
        }

    }
}

void PhysicsProcesser::CheckCrash() {

    for (auto &boxCollider: BoxColliders) {
        if(boxCollider->GetOwner()->GetComponent<Rigidbody>()==nullptr)
            continue;
        bool IsCrashed = false;

        for (auto &boxCollider_: BoxColliders) {
            if(boxCollider==boxCollider_)
                continue;
            if (boxCollider->CheckCrash(*boxCollider_)) {
                if(std::find(FixPosColliders.begin(),
                             FixPosColliders.end(),
                             boxCollider) == FixPosColliders.end())
                    FixPosColliders.emplace_back(boxCollider);
                IsCrashed = true;
            }
        }

        for (auto &lineCollider_: LineColliders) {
            if (boxCollider->CheckCrash(*lineCollider_)) {
                if(std::find(FixPosColliders.begin(),
                             FixPosColliders.end(),
                             boxCollider) == FixPosColliders.end())
                    FixPosColliders.emplace_back(boxCollider);
                IsCrashed = true;
            }
        }

        if(!IsCrashed)
        {
            if(std::find(FixPosColliders.begin(),FixPosColliders.end(),boxCollider) != FixPosColliders.end())
            {
                auto iter = std::find(FixPosColliders.begin(), FixPosColliders.end(), boxCollider);
                FixPosColliders.erase(iter);
            }
        }

        boxCollider->UpdateCrashFlag();
    }
    for (auto &lineCollider: LineColliders) {
        if(lineCollider->GetOwner()->GetComponent<Rigidbody>()==nullptr)
            continue;
        bool IsCrashed = false;

        for (auto &_boxCollider: BoxColliders) {
            if(lineCollider->GetOwner()==_boxCollider->GetOwner())
                continue;
            if (lineCollider->CheckCrash(*_boxCollider)) {
                if(std::find(FixPosColliders.begin(),
                             FixPosColliders.end(),
                             lineCollider) == FixPosColliders.end())
                    FixPosColliders.emplace_back(lineCollider);
                IsCrashed = true;
            }
        }

        for (auto &_lineCollider: LineColliders) {
            if(lineCollider==_lineCollider)
                continue;
            if(lineCollider->GetOwner()==_lineCollider->GetOwner())
                continue;
            if (lineCollider->CheckCrash(*_lineCollider)) {
                if(std::find(FixPosColliders.begin(),
                             FixPosColliders.end(),
                             lineCollider) == FixPosColliders.end())
                    FixPosColliders.emplace_back(lineCollider);
                IsCrashed = true;
            }
        }

        if(!IsCrashed)
        {
            if(std::find(FixPosColliders.begin(),FixPosColliders.end(),lineCollider) != FixPosColliders.end())
            {
                auto iter = std::find(FixPosColliders.begin(), FixPosColliders.end(), lineCollider);
                FixPosColliders.erase(iter);
            }
        }

        lineCollider->UpdateCrashFlag();
    }

//    SPDLOG_INFO("BoxColliders {}",BoxColliders.size());
//    SPDLOG_INFO("LineColliders {}",LineColliders.size());
//    SPDLOG_INFO("FixPosColliders {}",FixPosColliders.size());
}

void PhysicsProcesser::AddCollider(BoxCollider *collider) {
    int MyColliderOrder =(int)collider->GetColliderType();
    auto iter = BoxColliders.begin();
    for( ; iter != BoxColliders.end() ; ++iter){
        int val =(*iter)->GetColliderType();
        if(MyColliderOrder > val){
            break;
        }
    }
    BoxColliders.insert(iter,collider);
}
void PhysicsProcesser::AddCollider(LineCollider *collider) {
    int MyColliderOrder =(int)collider->GetColliderType();
    auto iter = LineColliders.begin();
    for( ; iter != LineColliders.end() ; ++iter){
        int val =(*iter)->GetColliderType();
        if(MyColliderOrder > val){
            break;
        }
    }
    LineColliders.insert(iter,collider);
}

void PhysicsProcesser::DeleteCollider(BoxCollider* collider) {
    auto iter = std::find(BoxColliders.begin(), BoxColliders.end(), collider);
    if (iter != BoxColliders.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, BoxColliders.end() - 1);
        BoxColliders.pop_back();
    }
    CleanCollider(collider);
}
void PhysicsProcesser::DeleteCollider(LineCollider* collider) {
    auto iter = std::find(LineColliders.begin(), LineColliders.end(), collider);
    if (iter != LineColliders.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, LineColliders.end() - 1);
        LineColliders.pop_back();
    }
    CleanCollider(collider);
}
void PhysicsProcesser::CleanCollider(Collider *collider) {
    auto iter = std::find(FixPosColliders.begin(),
                              FixPosColliders.end(),
                              collider);
    if (iter != FixPosColliders.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, FixPosColliders.end() - 1);
        FixPosColliders.pop_back();
    }

    for(auto& col : FixPosColliders)
    {
        auto iter = std::find(col->CrashedColliders.begin(),
                              col->CrashedColliders.end(),
                              collider);
        if (iter != col->CrashedColliders.end())
        {
            // Swap to end of vector and pop off (avoid erase copies)
            std::iter_swap(iter, col->CrashedColliders.end() - 1);
            col->CrashedColliders.pop_back();
        }
    }
}
void PhysicsProcesser::Finalize() {}
PhysicsProcesser::~PhysicsProcesser() {}
