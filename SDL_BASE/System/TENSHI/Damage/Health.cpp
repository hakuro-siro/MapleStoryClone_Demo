//
// Created by binetsu on 12/14/24.
//

#include "Health.h"
#include "DamageHandler.h"
#include "System/Utility/Singleton.h"

Health::Health(class GameObject* owner,int Maxhp, int updateOrder):
    Component(owner),
    MaxHp(Maxhp),
    CurrentHP(MaxHp)
{


}


void Health::GetDamage(vector<int> damageList) {
    if(!Alive)
        return;
    Singleton<DamageHandler>::GetInstance().OnDamageHandled(
            mOwner,damageList);

    OnDamaged.OnNext(1);
    for(auto& dmg : damageList){
        CurrentHP -= dmg;
        if(CurrentHP<=0){
            CurrentHP = 0;
            Alive = false;
            OnDead.OnNext(1);
            break;
        }
    }
}


Health::~Health(){

}