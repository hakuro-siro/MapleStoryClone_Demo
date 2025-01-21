//
// Created by binetsu on 9/7/24.
//
#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "System/Utility/Math.h"
#include "System/Data/GameObjectData.h"
#include "System/Data/TileData.h"
using namespace std;
#include "System/Data/AssetPath.h"

enum SceneType {
    T_TitleScene = 0,
    T_LoginScene = 1,
    T_LoadingScene = 2,
    T_InGameScene = 3
};
const std::unordered_map<std::string,SceneType> SceneMap {
        {"TitleScene",SceneType::T_TitleScene},
        {"LoginScene",SceneType::T_LoginScene},
        {"LoadingScene",SceneType::T_LoadingScene},
        {"InGameScene",SceneType::T_InGameScene}
};

class Scene{

public:
    // Scene 내부 Object 리스트 데이터
    string SceneData_MASTERDIR;
    string SceneCode;
    /// DATA FIELD
    /// 어디까지나 데이터 격납용
    SceneType mSceneType;
    // Scene 내부 Collider의 맵 데이터
    string ColliderData_DIR;
    // TileMap Data - Layer 저장
    vector<string> TileData_DIR;
    // TileTheme 데이터
    string TileTheme_DIR;
    int MaxLimitX = 1024;
    int MaxLimitY = 720;
    string PortalGo = "Scene/InGameScene/MapData/BurnedHene_01_Data.json";
    /// Real Objects of Scene
    unordered_map<string,GameObject*> GameObjects;
};
const string SceneNameKey = "SceneName";
const string GameObjectsKey= "GameObjects";
const string MonsterObjectsKey= "MonsterObjects";
const string MapDataDir_Key= "MapDataDir";
const string MaxLimitX_Key= "MaxLimitX";
const string MaxLimitY_Key= "MaxLimitY";
const string ProbDataDir_Key= "ProbDataDir";
const string ColliderDataDir_Key= "ColliderDataDir";
const string PortalGo_Key = "PortalGo";


