//
// Created by binetsu on 9/7/24.
//

#include <vector>
#include <SDL2/SDL.h>
#include "System/Utility/Singleton.h"
#include "System/Component/Camera/Camera.h"
#include "IProcess.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 700
class Renderer : IProcess ,Singleton<Renderer>{
public:

    //Construct
    Renderer();
    ~Renderer();

    bool Initialize() override;
    void Update(float deltaTime) override;
    void Finalize() override;

    // Add Sprite in Vector Sprites
    void AddSprite(class Sprite* sprite);
    // Delete Sprite in Vector Sprites
    void RemoveSprite(class Sprite* sprite);

    // Add Sprite in Vector Sprites
    void AddText(class Text* text);
    // Delete Sprite in Vector Sprites
    void RemoveText(class Text* sprite);

#ifdef _DEBUG
    void AddDebugRay(class DebugRay* ray);
    void RemoveDebugRay(class DebugRay* ray);
#endif

    class GameObject* MainCamera;
    class GameObject* UICamera;
    class Camera* MainCameraComp;
    /// Getter
    std::vector<class Sprite*> GetSprites() const {  return mSprites;};
    SDL_Window* GetWindow() const { return  mWindow; }
    SDL_Renderer* GetRenderer() const { return mRenderer;}
    /// Setter
    void ClearSprites();
    void Render();
    void Shutdown();
private:
    // Vector of Sprites
    std::vector<class Sprite*> mSprites;
    std::vector<class Text*> mTexts;
#ifdef _DEBUG
    std::vector<class DebugRay*> mRays;
#endif
    // Window created by SDL
    SDL_Window* mWindow = nullptr;
    // Renderer for 2D drawing
    SDL_Renderer* mRenderer = nullptr;
};

