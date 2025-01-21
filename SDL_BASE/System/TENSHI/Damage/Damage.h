//
// Created by binetsu on 12/14/24.
//

#pragma once
#include "System/GameObject/GameObject.h"
#include <unordered_map>
#include "System/Data/AssetPath.h"
#include "System/Component/SpriteComponent.h"

using namespace std;

const std::unordered_map<int,string> DamageNumMap {
        {0,DAMAGE_CRITICAL_0},
        {1,DAMAGE_CRITICAL_1},
        {2,DAMAGE_CRITICAL_2},
        {3,DAMAGE_CRITICAL_3},
        {4,DAMAGE_CRITICAL_4},
        {5,DAMAGE_CRITICAL_5},
        {6,DAMAGE_CRITICAL_6},
        {7,DAMAGE_CRITICAL_7},
        {8,DAMAGE_CRITICAL_8},
        {9,DAMAGE_CRITICAL_9},
};

class Damage
{
public:
    Damage(class GameObject* obj);
    ~Damage();
    void UpdateDamageLifeTime(float deltaTime);
    void SetDamage(int dmg);
    class GameObject* DamageObject;
    float DamageLifeTime = 1;
    float CurrentLifeTime = 0;
    bool Damaged = true;
private:
    vector<SDL_Texture*> DamageTextures;
    vector<SpriteComponent*> DamageTextureComponents;
    vector<int> DamageNumbers;
    int Get10000(int val) { return val/10000; }
    int Get1000(int val) { return GetP1000(val)/1000; }
    int Get100(int val) { return GetP100(val)/100; }
    int Get10(int val) { return GetP10(val)/10; }

    int GetP1000(int val) { return val%10000; }
    int GetP100(int val) { return val%1000; }
    int GetP10(int val) { return val%100; }
    int GetP1(int val) { return val%10; }
};

