//
// Created by binetsu on 9/7/24.
//
#include "EnemyData.h"
#include "GameObjectData.h"
#include <string>

EnemyData::EnemyData(const json& data) {
    auto iter =MonsterMap.find(data.at(MonsterType_Key).get<std::string>());
    if(iter!=MonsterMap.end())
        Type = iter->second;
    MonsterDataPath = data.at(MonsterDataPath_Key).get<std::string>();
    ObjectPosition_X  = stof(data.at(ObjectPosition_X_Key).get<std::string>());
    ObjectPosition_Y = stof(data.at(ObjectPosition_Y_Key).get<std::string>());
}