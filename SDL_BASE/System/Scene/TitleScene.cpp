//
// Created by binetsu on 9/7/24.
//

#include "TitleScene.h"
#include "System/Data/AssetPath.h"

TitleScene::TitleScene() {
    // InGameSceneData (JSON)
    SceneData_MASTERDIR = SCENE_DIR+TITLE_SCENE_DIR+TITLE_SCENE_DATA;
    // Collider Map (CSV)
    ColliderData_DIR = SCENE_DIR+TITLE_SCENE_DIR+INGAME_SCENE_COLLIDER_DATA;

    mSceneType = SceneType::T_TitleScene;
    // Tile Data (CSV)
}
