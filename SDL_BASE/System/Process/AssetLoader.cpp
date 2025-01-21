//
// Created by binetsu on 9/7/24.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "AssetLoader.h"
#include "System/GameObject/GameObject.h"
#include "Processer.h"
#include "Renderer.h"
#include "System/TENSHI/Player/Player.h"
#include "System/Data/AssetPath.h"
#include "System/Scene/Scene.h"
#include "fstream"
#include "System/Data/AnimSpriteData.h"
#include "System/Component/SpriteComponent.h"
#include "System/Physics/BoxCollider.h"
#include "System/Physics/LineCollider.h"
#include "PhysicsProcesser.h"
#include "Sprite.h"
#include "System/TENSHI/Player/Skill/Skill.h"
#include "System/Component/TextComponent.h"
#include "System/Data/LineColliderData.h"
#include "System/TENSHI/Enemy/Enemy.h"
#include "System/Data/EnemyData.h"
#include "System/TENSHI/Enemy/EnemyManager.h"
#include "System/Data/MonsterData.h"
#include "System/TENSHI/Damage/DamageHandler.h"
#include "System/TENSHI/Prob/Portal.h"
#include "System/UI/View/TitleCanvas.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

AssetLoader::AssetLoader() {}

bool AssetLoader::Initialize()
{

    IProcess::Initialize();

    Bind_Processer = true;
    return true;
}

void AssetLoader::Update(float deltaTime)
{
}

/*
 * Load Data
 * Load InGame Assets (Also Class)
 * Like GameObjectManager
 */
bool AssetLoader::LoadSceneData(Scene *scene)
{
    SPDLOG_INFO("{}", scene->SceneData_MASTERDIR);
    CurrentScene = scene;
    string pth = scene->SceneData_MASTERDIR;
    json data = ReadJson(scene->SceneData_MASTERDIR);

    switch (scene->mSceneType)
    {
    case SceneType::T_TitleScene:
        LoadTitleScene(data);
        break;
    case SceneType::T_LoadingScene:
        LoadLoadingScene(data);
        break;
    case SceneType::T_LoginScene:
        LoadLoginScene(data);
        break;
    case SceneType::T_InGameScene:
        LoadInGameScene(data);
        break;
    }
    return true;
}

bool AssetLoader::LoadInGameScene(json &scene)
{

    vector<GameObjectData> GameObjects;

    for (const auto &object : scene.at(GameObjectsKey))
    {
        GameObjects.emplace_back(GameObjectData(object));
    }

    for (auto &gameobject : GameObjects)
    {
        switch (gameobject.Type)
        {
        case GameObjectType::PlayerObject:
            if (mPlayer == nullptr)
                LoadPlayer(&gameobject);
            break;
        case GameObjectType::SpriteObject:
            LoadSpriteObject(&gameobject);
            break;
        }
    }

    json data = ReadJson(scene.at(MapDataDir_Key));
    LoadInGameMap(data);
    auto dmgHandler = new DamageHandler();
    return true;
}

bool AssetLoader::LoadLoginScene(json &scene)
{
    return true;
}

bool AssetLoader::LoadTitleScene(json &scene)
{
    TitleCanvas *titleCanvas = new TitleCanvas();
    titleCanvas->Initialize();

    vector<GameObjectData> GameObjects;
    for (const auto &object : scene.at(GameObjectsKey))
    {
        GameObjects.emplace_back(GameObjectData(object));
    }

    for (auto &gameobject : GameObjects)
    {
        switch (gameobject.Type)
        {
        case GameObjectType::PlayerObject:
            if (mPlayer == nullptr)
                LoadPlayer(&gameobject);
            break;
        case GameObjectType::SpriteObject:
            LoadSpriteObject(&gameobject);
            break;
        }
    }

    json data = ReadJson(scene.at(MapDataDir_Key));
    LoadInGameMap(data);
    return true;
}

bool AssetLoader::LoadLoadingScene(json &scene)
{
    return true;
}

bool AssetLoader::GoPortalInGameMap()
{
    json data = ReadJson(CurrentScene->PortalGo);
    LoadInGameMap(data);
    Singleton<Processer>::GetInstance().SceneMoving = false;
    return true;
}

bool AssetLoader::LoadInGameMap(json &map)
{
    json prob = ReadJson(map.at(ProbDataDir_Key));
    LoadProb(prob);
    json Col = ReadJson(map.at(ColliderDataDir_Key));
    LoadCollider(Col);
    CurrentScene->PortalGo = map.at(PortalGo_Key);

    auto MaxLimitX = stoi(map.at(MaxLimitX_Key).get<std::string>());
    auto MaxLimitY = stoi(map.at(MaxLimitY_Key).get<std::string>());
    Singleton<Renderer>::GetInstance().MainCameraComp->MaxLimitX = MaxLimitX;
    Singleton<Renderer>::GetInstance().MainCameraComp->MaxLimitY = MaxLimitY;

    return true;
}

void AssetLoader::LoadProb(json &data)
{
    vector<GameObjectData> GameObjects;

    for (const auto &object : data.at(GameObjectsKey))
    {
        GameObjects.emplace_back(GameObjectData(object));
    }

    for (auto &gameobject : GameObjects)
    {
        switch (gameobject.Type)
        {
        case GameObjectType::PlayerObject:
            if (mPlayer == nullptr)
                LoadPlayer(&gameobject);
            else
                mPlayer->SetPosition(
                    Vector2(
                        gameobject.ObjectPosition_X, gameobject.ObjectPosition_Y));
            break;
        case GameObjectType::SpriteObject:
            LoadSpriteObject(&gameobject);
            break;
        case GameObjectType::PortalObject:
            LoadPortal(&gameobject);
            break;
        }
    }
    vector<EnemyData *> Enemys;

    for (const auto &enemy : data.at(MonsterObjectsKey))
    {
        Enemys.emplace_back(new EnemyData(enemy));
    }
    auto EnemyManagerObj = new GameObject();
    auto mEnemyManager = new EnemyManager(EnemyManagerObj);
    mEnemyManager->SetEnemyData(Enemys);

    for (auto &enemy : Enemys)
    {
        switch (enemy->Type)
        {
        case MonsterType::CommonMonster:
            LoadEnemy(enemy, mEnemyManager);
            break;
        case MonsterType::BossMonster:
            LoadEnemy(enemy, mEnemyManager);
            break;
        }
    }
}

void AssetLoader::LoadCollider(json &data)
{

    vector<LineColliderData> LineColliders;

    for (const auto &object : data.at(ColliderMap_Key))
    {
        LineColliders.emplace_back(LineColliderData(object));
    }
    auto ColliderObject = new GameObject();
    ColliderObject->SetPosition(
        Vector2::Zero);
    for (auto &col : LineColliders)
    {
        auto lineCollider = new LineCollider(ColliderObject, 10);
        if (col.PosA.x == col.PosB.x)
            lineCollider->SetColliderLayer(ColliderLayer::L_Wall);
        else
            lineCollider->SetColliderLayer(ColliderLayer::L_Ground);
        lineCollider->SetPosA(&col.PosA);
        lineCollider->SetPosB(&col.PosB);
    }
}

// 이미지로 로드하는 맵 + 콜라이더 맵이랑같이 병용
void AssetLoader::LoadSpriteObject(GameObjectData *data)
{
    auto *MapObject = new GameObject();
    MapObject->SetPosition(Vector2(data->ObjectPosition_X, data->ObjectPosition_Y));
    SpriteComponent *spriteComp = new SpriteComponent(MapObject, 10);
    SDL_Texture *Tex = GetTexture(data->SpriteDir);
    spriteComp->SetTexture(Tex);
}
void AssetLoader::LoadPortal(GameObjectData *data)
{
    auto *mPortal = new Portal();
    mPortal->SetPosition(Vector2(data->ObjectPosition_X, data->ObjectPosition_Y));
    SpriteComponent *spriteComp = new SpriteComponent(mPortal, 10);
    SDL_Texture *Tex = GetTexture(data->SpriteDir);
    spriteComp->SetTexture(Tex);
    mPortal->Trigger = new BoxCollider(mPortal);
    mPortal->Trigger->SetHeight(140);
    mPortal->Trigger->SetWidth(104);
    mPortal->Trigger->SetColliderLayer(ColliderLayer::L_Player);
    mPortal->Trigger->UpdateColliderData();
    mPortal->Trigger->OnlyTrigger = true;
}
/// Player Load
void AssetLoader::LoadPlayer(GameObjectData *data)
{
    json Skilldata = ReadJson(PLAYER_SKILL_DATA_DIR);
    vector<string> PlayerSkillData;

    for (const auto &skill : Skilldata.at(PlayerSkillsKey))
    {
        PlayerSkillData.emplace_back(skill.get<std::string>());
    }
    mPlayer = new Player(Vector2(data->ObjectPosition_X, data->ObjectPosition_Y));
    mPlayer->Bind_Processer = true;
    for (auto &skill : PlayerSkillData)
    {
        json skilldata = ReadJson(SKILL_DIR + skill);
        auto mSkill = new Skill(skilldata);
        for (const auto &dir : skilldata.at(SkillImgDIRKey))
        {
            mSkill->SkillImgDIR.emplace_back(dir.get<std::string>());
        }
        for (const auto &dir : skilldata.at(FxImgDIRKey))
        {
            mSkill->FxImgDIR.emplace_back(dir.get<std::string>());
        }
        SPDLOG_INFO("{}", mSkill->mSkillKey);
        mPlayer->PlayerSkills[mSkill->mSkillKey] = mSkill;
    }
    // Load Player(Skill) Logic?
    mPlayer->SetScale(1.0f);
}
/// Enemy Load
void AssetLoader::LoadEnemy(EnemyData *data, EnemyManager *manager)
{
    json monData = ReadJson(data->MonsterDataPath);
    auto mMonsterData = new MonsterData(monData);
    for (const auto &skill : monData.at(IdleImg_Key))
    {
        mMonsterData->IdleImgDIR.emplace_back(skill.get<std::string>());
    }
    for (const auto &skill : monData.at(MoveImg_Key))
    {
        mMonsterData->MoveImgDIR.emplace_back(skill.get<std::string>());
    }
    for (const auto &skill : monData.at(AttackImg_Key))
    {
        mMonsterData->AttackImgDIR.emplace_back(skill.get<std::string>());
    }
    for (const auto &skill : monData.at(DeadImg_Key))
    {
        mMonsterData->DeadImgDIR.emplace_back(skill.get<std::string>());
    }
    for (const auto &skill : monData.at(HitImg_Key))
    {
        mMonsterData->HitImgDIR.emplace_back(skill.get<std::string>());
    }
    auto mEnemy = new Enemy(Vector2(data->ObjectPosition_X, data->ObjectPosition_Y), mMonsterData, data, manager);

    // Load Player(Skill) Logic?
    mEnemy->SetScale(1.0f);
}

/// Animation Load
std::vector<AnimSpriteData> AssetLoader::LoadAnimSpriteData(const std::string &fileName)
{
    json data = ReadJson(fileName);
    std::vector<AnimSpriteData> output;
    for (const auto &sprite : data.at(AnimSprite_Key))
    {
        output.push_back(AnimSpriteData(sprite));
    }
    return output;
}

void AssetLoader::Finalize()
{
    UnloadData();
}

/*
 * UnLoad Data
 */
void AssetLoader::UnloadData()
{
    // Destroy textures
    for (auto i : mTextures)
    {
        SDL_DestroyTexture(i.second);
    }

    mTextures.clear();
}

// Json && CSV
json AssetLoader::ReadJson(std::string fileName)
{
    string path = ASSET_DIR + BASE_DIR + fileName;
    std::ifstream Jsonfile(path);
    if (!Jsonfile.is_open())
    {
        SDL_Log("Can not Open Json File Path : %s", path.c_str());
        return nullptr;
    }
    json j;
    Jsonfile >> j;
    return j;
}
vector<vector<string>> AssetLoader::ReadCSV(std::string fileName)
{
    vector<vector<string>> CSVdata = vector<vector<string>>();

    std::ifstream file(fileName);
    if (!file.is_open())
    {
        SDL_Log("Can not Open CSV File Path : %s", fileName.c_str());
        return CSVdata;
    }
    std::string line;

    while (std::getline(file, line))
    {
        stringstream ss(line);
        string field;
        vector<string> fields;
        while (getline(ss, field, ','))
        {
            fields.push_back(field);
        }
        CSVdata.push_back(fields);
    }
    return CSVdata;
}

/// Get Texture
SDL_Texture *AssetLoader::GetTexture(const std::string &fileName, int FrameCount)
{
    std::string path = ASSET_DIR + BASE_DIR + fileName;
    SDL_Texture *tex = nullptr;
    // Is the texture already in the map?

    auto iter = mTextures.find(path);
    if (iter != mTextures.end())
    {
        tex = iter->second;
    }
    else
    {
        tex = LoadTexture(path);

        mTextures.emplace(path.c_str(), tex);
    }
    return tex;
}

/// Load Texture
SDL_Texture *AssetLoader::LoadTexture(const std::string &fileName)
{

    // Load from file
    SDL_Surface *surf = IMG_Load(fileName.c_str());
    if (!surf)
    {
        SPDLOG_ERROR("Failed to load texture file {}", fileName.c_str());
        return nullptr;
    }

    // Create texture from surface
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Singleton<Renderer>::GetInstance().GetRenderer(), surf);
    SDL_FreeSurface(surf);
    if (!tex)
    {
        SPDLOG_ERROR("Failed to convert surface to texture for {}", fileName.c_str());
        return nullptr;
    }
    return tex;
}

/// Text && Fonts
SDL_Texture *AssetLoader::GetText(const std::string &Message,
                                  const std::string &Font,
                                  int Size,
                                  int R, int G, int B)
{

    SDL_Color color = {static_cast<Uint8>(R),
                       static_cast<Uint8>(G),
                       static_cast<Uint8>(B)};
    return SDL_CreateTextureFromSurface(
        Singleton<Renderer>::GetInstance().GetRenderer(),
        TTF_RenderText_Solid(GetFont(Font, Size),
                             Message.c_str(),
                             color));
}
TTF_Font *AssetLoader::GetFont(const std::string &fileName, int FontSize)
{
    std::string path = ASSET_DIR + BASE_DIR + FONT_DIR + fileName;
    TTF_Font *fnt = nullptr;
    // Is the texture already in the map?

    auto iter = mFonts.find(fileName + to_string(FontSize));
    if (iter != mFonts.end())
    {
        fnt = iter->second;
    }
    else
    {
        fnt = LoadFont(path, FontSize);
        mFonts.emplace(fileName + to_string(FontSize), fnt);
    }
    return fnt;
}
TTF_Font *AssetLoader::LoadFont(string path, int FontSize)
{
    string PATH = path;
    TTF_Font *Loadedfont = TTF_OpenFont(PATH.c_str(), FontSize);

    if (!Loadedfont)
    {
        SPDLOG_ERROR("NULL font => {}", SDL_GetError());
        return Loadedfont;
    }
    else
    {
        SPDLOG_INFO("Loaded Font => {}", PATH);
    }
    return Loadedfont;
}

/// Tile (Delete)
vector<vector<string>> AssetLoader::LoadTileMapdata(std::string fileName)
{
    string path = ASSET_DIR + BASE_DIR + fileName;
    return ReadCSV(path);
}
