//
// Created by binetsu on 9/16/24.
//

#include "TileData.h"


TileData::TileData(const json &data) {
    auto Codeiter= TileCodeMap.find(stoi(data.at(TileCodeKey).get<std::string>()));
    if(Codeiter!=TileCodeMap.end())
        mTileCode = Codeiter->second;

    TileSpritePath = data.at(TileSpritePathKey).get<std::string>();

    auto ColTypeiter = TileColliderMap.find(data.at(TileColliderTypeKey).get<std::string>());
    if(ColTypeiter!=TileColliderMap.end())
        mColliderType = ColTypeiter->second;

    mColliderPositionX = stof(data.at(TileColliderPosXKey).get<std::string>());
    mColliderPositionY = stof(data.at(TileColliderPosYKey).get<std::string>());

    mColliderAngle  = stoi(data.at(TileColliderAngleKey).get<std::string>());
}
TileData::~TileData(){

}