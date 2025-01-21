//
// Created by binetsu on 12/14/24.
//

#include "DamageHandler.h"
#include "Damage.h"

DamageHandler::DamageHandler() {

}
bool DamageHandler::Initialize(){
    IProcess::Initialize();
    Bind_Processer = true;
    return true;
}

void DamageHandler::Update(float deltaTime) {
    for(auto& dmg : Damages){
        dmg->UpdateDamageLifeTime(deltaTime);
    }
    for(auto& dmg : Damages){
        if(dmg->CurrentLifeTime>=dmg->DamageLifeTime)
        {
            DeadDamages.emplace_back(dmg);
        }
    }
    for(auto& dmg : DeadDamages){
        auto diter = std::find(Damages.begin(), Damages.end(), dmg);
        if (diter != Damages.end())
        {
            std::iter_swap(diter, Damages.end() - 1);
            Damages.pop_back();
        }
        delete dmg;
    }
    DeadDamages.clear();
}

void DamageHandler::Finalize() {

}

void DamageHandler::OnDamageHandled(GameObject* DamagedObject, vector<int> damageList)
{
    auto DamageGameObj = new GameObject();
    DamageGameObj->SetPosition(DamagedObject->GetPosition()+Vector2(0,0));
    auto dmg = new Damage(DamageGameObj);
    dmg->SetDamage(90000);
    auto DamageGameObj1 = new GameObject();
    DamageGameObj1->SetPosition(DamagedObject->GetPosition()+Vector2(0,30));
    auto dmg1 = new Damage(DamageGameObj1);
    dmg1->SetDamage(90000);
    auto DamageGameObj2 = new GameObject();
    DamageGameObj2->SetPosition(DamagedObject->GetPosition()+Vector2(0,60));
    auto dmg2 = new Damage(DamageGameObj2);
    dmg2->SetDamage(90000);

    Damages.emplace_back(dmg);

    Damages.emplace_back(dmg1);

    Damages.emplace_back(dmg2);
}
