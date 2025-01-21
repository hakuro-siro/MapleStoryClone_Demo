//
// Created by binetsu on 9/7/24.
//
#include "GameObjectData.h"
#include <string>

GameObjectData::GameObjectData(const json& data) {
    auto iter =ObjectMap.find(data.at(GameObjectType_Key).get<std::string>());
    if(iter!=ObjectMap.end())
        Type = iter->second;
    SpriteDir = data.at(SpriteDir_Key).get<std::string>();
    ObjectPosition_X  = stof(data.at(ObjectPosition_X_Key).get<std::string>());
    ObjectPosition_Y = stof(data.at(ObjectPosition_Y_Key).get<std::string>());
}