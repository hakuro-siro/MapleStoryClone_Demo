//
// Created by binetsu on 11/26/24.
//

#include "SceneManager.h"

SceneManager::SceneManager()
{
}

bool SceneManager::Initialize()
{
    IProcess::Initialize();
    return true;
}

void SceneManager::ChangeScene(Scene_Code SceneCode)
{
}

void SceneManager::Finalize()
{
    IProcess::Finalize();
}
SceneManager::~SceneManager()
{
}
