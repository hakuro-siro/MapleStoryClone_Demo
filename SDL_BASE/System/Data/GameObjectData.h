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

enum GameObjectType{
    PlayerObject,
    SpriteObject,
    PortalObject
};
const std::unordered_map<std::string,GameObjectType> ObjectMap{
        {"PlayerObject",GameObjectType::PlayerObject},
        {"SpriteObject",GameObjectType::SpriteObject},
        {"Portal",GameObjectType::PortalObject}
};

class GameObjectData{

public:
    GameObjectData(const json& data);
    GameObjectType Type;
    string SpriteDir;
    float ObjectPosition_X;
    float ObjectPosition_Y;
};
const string SpriteDir_Key = "SpriteDir";
const string GameObjectType_Key = "Type";
const string ObjectPosition_X_Key = "ObjectPosition_X";
const string ObjectPosition_Y_Key= "ObjectPosition_Y";