//
// Created by binetsu on 9/16/24.
//

#pragma once
#include "json.hpp"
#include "System/Physics/Collider.h"
#include <string>

using namespace std;
using json = nlohmann::json;

enum TileCode{
    //Floor
    T_500001,
    //NONF
    T_500002,
    //Floor
    T_500003,
    T_500004,
    T_500005,
    //Floor Edge
    T_500006,
    T_500007,
    T_500008,
    T_000000
};
const std::unordered_map<int,TileCode> TileCodeMap{
        {500001,TileCode::T_500001},
        {500002,TileCode::T_500002},
        {500003,TileCode::T_500003},
        {500004,TileCode::T_500004},
        {500005,TileCode::T_500005},
        {500006,TileCode::T_500006},
        {500007,TileCode::T_500007},
        {500008,TileCode::T_500008},
        {000000,TileCode::T_000000}
};
const std::unordered_map<string,ColliderType> TileColliderMap{
        {"LineCol",ColliderType::LineCol},
        {"NoCol",ColliderType::NoCol},
        {"BoxCol",ColliderType::BoxCol}
};

class TileData {

public:
    TileData(const json& data);
    ~TileData();
    TileCode mTileCode;

    string TileSpritePath;

    ColliderType mColliderType = ColliderType::NoCol;
    float mColliderPositionX = 0.0f;
    float mColliderPositionY = 0.0f;
    int mColliderAngle = 0;
};

const string TileDatasKey = "TileDatas";
const string TileCodeKey = "TileCode";
const string TileSpritePathKey = "TileSpritePath";

const string TileColliderTypeKey = "ColliderType";
const string TileColliderPosXKey = "ColliderPosX";
const string TileColliderPosYKey = "ColliderPosY";
const string TileColliderAngleKey = "ColliderAngle";