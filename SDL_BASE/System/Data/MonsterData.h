//
// Created by binetsu on 12/11/24.
//

#pragma once
#include <string>
using namespace std;
#include "json.hpp"
using json = nlohmann::json;

class MonsterData {
public:
    MonsterData(const json& data);
    ~MonsterData();
    vector<string> IdleImgDIR;
    vector<string> AttackImgDIR;
    vector<string> MoveImgDIR;
    vector<string> DeadImgDIR;
    vector<string> HitImgDIR;
    float Monster_Width;
    float Monster_Height;
};


const string IdleImg_Key = "IdleImgDIR";
const string AttackImg_Key = "AttackImgDIR";
const string MoveImg_Key = "MoveImgDIR";
const string DeadImg_Key = "DeadImgDIR";
const string HitImg_Key = "HitImgDIR";
const string Monster_Width_Key = "Monster_Width";
const string Monster_Height_Key = "Monster_Height";