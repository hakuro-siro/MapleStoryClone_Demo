//
// Created by binetsu on 9/7/24.
//

#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include <unordered_map>
#include <string>
#include "json.hpp"
#include "System/Utility/Singleton.h"
#include "IProcess.h"

using json = nlohmann::json;
class AssetLoader : IProcess ,Singleton<AssetLoader>
{
public:
    AssetLoader();

    bool Initialize() override;
    void Update(float deltaTime) override;
    void Finalize() override;

    ///Scene Load
    bool LoadSceneData(class Scene* scene);

    bool LoadInGameScene(json& scene);
    bool LoadTitleScene(json& scene);
    bool LoadLoginScene(json& scene);
    bool LoadLoadingScene(json& scene);

    bool GoPortalInGameMap();
    bool LoadInGameMap(json& map);

    // Get Texture (Load Image)
    SDL_Texture* GetTexture(const std::string& fileName , int FrameCount = 0);
    // Get Font (Load Font)
    TTF_Font* GetFont(const std::string& fileName,int FontSize);
    SDL_Texture* GetText(const std::string& Message,const std::string& Font, int Size,
                         int R=255,int G=255, int B=255);
    std::vector<class AnimSpriteData> LoadAnimSpriteData(const std::string& fileName);
    void UnloadData();

    void LoadEnemy(class EnemyData* data,class EnemyManager* manager);
    json ReadJson(std::string fileName);

    class Player* mPlayer;

    class Scene* CurrentScene;
private:
    SDL_Texture* LoadTexture(const std::string & fileName);
    TTF_Font* LoadFont(std::string path, int FontSize);
    std::vector<std::vector<std::string>> ReadCSV(std::string fileName);
    std::vector<std::vector<std::string>> LoadTileMapdata(std::string  fileName);

    void LoadSpriteObject(class GameObjectData* data);
    void LoadPortal(class GameObjectData* data);
    void LoadPlayer(class GameObjectData* data);

    void LoadCollider(json& data);
    void LoadProb(json& data);

    // Map of textures loaded
    std::unordered_map<std::string, SDL_Texture*> mTextures;
    // Map of fontes loaded
    std::unordered_map<std::string, TTF_Font *> mFonts;

    std::vector<std::vector<std::string>> CurrentMapdata;


};
