//
// Created by binetsu on 9/7/24.
//

#include "InGameScene.h"
#include "System/Data/AssetPath.h"

InGameScene::InGameScene() {
    // InGameSceneData (JSON)
    SceneData_MASTERDIR = SCENE_DIR+INGAME_SCENE_DIR+INGAME_SCENE_DATA;
    // Collider Map (CSV)
    ColliderData_DIR = SCENE_DIR+INGAME_SCENE_DIR+INGAME_SCENE_COLLIDER_DATA;

    mSceneType = SceneType::T_InGameScene;
    // Tile Data (CSV)
//    TileDataDIR.emplace_back(SCENE_DIR+INGAME_SCENE_DIR+INGAME_SCENE_TILE_DATA_LAYER_0);
//    TileDataDIR.emplace_back(SCENE_DIR+INGAME_SCENE_DIR+INGAME_SCENE_TILE_DATA_LAYER_2);
//    TileDataDIR.emplace_back(SCENE_DIR+INGAME_SCENE_DIR+INGAME_SCENE_TILE_DATA_LAYER_1);
//    // Tile Theme
//    TileThemeDIR = TILE_DIR+T_LISPORT+TILE_DATA_DIR;
}
