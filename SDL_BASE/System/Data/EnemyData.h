//
// Created by binetsu on 9/7/24.
//

#pragma once
#include <string>
#include <unordered_map>
#include "System/Utility/Math.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

enum MonsterType{
    CommonMonster,
    BossMonster
};
const std::unordered_map<std::string,MonsterType> MonsterMap{
        {"CommonMonster",MonsterType::CommonMonster},
        {"BossMonster",MonsterType::BossMonster}
};

class EnemyData{

public:
    EnemyData(const json& data);
    MonsterType Type;
    string MonsterDataPath;
    float ObjectPosition_X;
    float ObjectPosition_Y;
};
const string MonsterType_Key = "MonsterType";
const string MonsterDataPath_Key = "MonsterDataPath";