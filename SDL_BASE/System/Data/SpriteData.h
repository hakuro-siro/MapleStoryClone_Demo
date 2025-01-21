//
// Created by binetsu on 9/8/24.
//

#pragma once
#include "json.hpp"
#include <string>

using namespace std;
using json = nlohmann::json;

class SpriteData{

public:
    SpriteData(const json& data);
    ~SpriteData();
    int X;
    int Y;
    int Width;
    int Height;
    int PivotX;
    int PivotY;
};

const string AnimSprite_Key = "Sprite";
const string X_Key = "X";
const string Y_Key = "Y";
const string Width_Key = "Width";
const string Height_Key = "Height";
const string PivotX_Key = "PivotX";
const string PivotY_Key = "PivotY";