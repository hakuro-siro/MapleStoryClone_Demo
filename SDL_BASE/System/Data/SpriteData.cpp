//
// Created by binetsu on 9/8/24.
//
#include "SpriteData.h"

SpriteData::SpriteData(const json &data) {
    X  = stoi(data.at(X_Key).get<std::string>());
    Y  = stoi(data.at(Y_Key).get<std::string>());
    Width  = stoi(data.at(Width_Key).get<std::string>());
    Height  = stoi(data.at(Height_Key).get<std::string>());
    PivotX = stoi(data.at(PivotX_Key).get<std::string>());
    PivotY = stoi(data.at(PivotY_Key).get<std::string>());
}