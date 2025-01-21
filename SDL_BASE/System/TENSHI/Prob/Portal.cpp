//
// Created by binetsu on 1/16/25.
//
#include "Portal.h"
#include "System/Physics/Collider.h"
#include "System/Physics/BoxCollider.h"
#include "System/TENSHI/Player/Player.h"
#include "System/Process/AssetLoader.h"
#include "System/Process/Processer.h"
#include "System/Physics/Rigidbody.h"
#include "System/Process/InputReader.h"
Portal::Portal():
GameObject(),
IinteractableObject(){
}
void Portal::Interact() {
    if(!IsPlayerOnThis)
        return;

    SPDLOG_INFO("Portal Interact");

    if(!Singleton<AssetLoader>::GetInstance().mPlayer->Isground||
            Singleton<AssetLoader>::GetInstance().mPlayer->mRigidBody->RigidVector.x!=0||
            Singleton<AssetLoader>::GetInstance().mPlayer->mRigidBody->RigidVector.y!=0)
        return;
    
    if(Singleton<InputReader>::GetInstance().MovementInputVector.x==0&&
            Singleton<InputReader>::GetInstance().MovementInputVector.y==0){
        Singleton<Processer>::GetInstance().ClearGameObject();
        Singleton<AssetLoader>::GetInstance().GoPortalInGameMap();
    }
}

void Portal::OnTriggerEnter(Collider &other) {
    //if(other.GetOwner()->GetComponent<Player>())
        SPDLOG_INFO("Trig Enter Portal");
        IsPlayerOnThis=true;
}

void Portal::OnTriggerExit(Collider &other) {
    //if(other.GetOwner()->GetComponent<Player>())
        SPDLOG_INFO("Trig Exit Portal");
    IsPlayerOnThis=false;
}


Portal::~Portal(){



}