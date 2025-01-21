//
// Created by binetsu on 9/7/24.
//

#include <algorithm>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Renderer.h"
#include "Processer.h"
#include "System/Component/SpriteComponent.h"

#include "System/GameObject/GameObject.h"
#include "Sprite.h"
#include "Text.h"

#ifdef _DEBUG
#include "System/Utility/DebugRay.h"
#endif

Renderer::Renderer() : mWindow(nullptr), mRenderer(nullptr)
{
    MainCamera = new GameObject();
    MainCamera->Bind_Processer = true;
    MainCameraComp = new Camera(MainCamera, 10,
                                0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

bool Renderer::Initialize()
{
    IProcess::Initialize();
    Bind_Processer = true;
    // Initialize SDL
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    TTF_Init();

    // Create an SDL Window
    mWindow = SDL_CreateWindow(
        "SDL_BASE", // Window title
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,  // Width of window
        WINDOW_HEIGHT, // Height of window
        0              // Flags (0 for no flags set)
    );

    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    //// Create SDL renderer
    mRenderer = SDL_CreateRenderer(
        mWindow, // Window to create renderer for
        -1,      // Usually -1
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    //// Create SDL IMAGE
    if (0 == IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
    {
        SDL_Log("Failed to Init Image: %s", SDL_GetError());
        return false;
    }

    return true;
}
/// Add SpriteComponent In Render Sprites Vector
void Renderer::AddSprite(Sprite *sprite)
{
    int myDrawOrder = sprite->GetDrawOrder();

    auto iter = mSprites.begin();

    for (; iter != mSprites.end(); ++iter)
    {
        if (myDrawOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }
    mSprites.insert(iter, sprite);
}
/// Add SpriteComponent In Render Sprites Vector
void Renderer::AddText(Text *text)
{
    int myDrawOrder = text->GetDrawOrder();

    auto iter = mTexts.begin();

    for (; iter != mTexts.end(); ++iter)
    {
        if (myDrawOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }
    mTexts.insert(iter, text);
}
void Renderer::ClearSprites()
{
    mSprites.clear();
}
/// Remove SpriteComponent In Render Sprites Vector
void Renderer::RemoveSprite(Sprite *sprite)
{
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}
void Renderer::RemoveText(Text *text)
{
    auto iter = std::find(mTexts.begin(), mTexts.end(), text);
    mTexts.erase(iter);
}
#ifdef _DEBUG
void Renderer::AddDebugRay(DebugRay *ray)
{
    mRays.push_back(ray);
}
void Renderer::RemoveDebugRay(DebugRay *ray)
{
    auto iter = std::find(mRays.begin(), mRays.end(), ray);
    mRays.erase(iter);
}
#endif

void Renderer::Update(float deltaTime)
{
}

SDL_Rect renderQuad;
SDL_Rect *RenderSize;
///  Renderer
void Renderer::
    Render()
{
    /// Set draw color to blue
    SDL_SetRenderDrawColor(
        mRenderer,
        0,  // R
        0,  // G
        0,  // B
        255 // A
    );

    /// Clear back buffer
    SDL_RenderClear(mRenderer);

    /// Draw all sprite components
    for (auto &sprite : mSprites)
    {
        RenderSize = sprite->GetRenderSize();
        bool isInViewport =
            RenderSize->x + RenderSize->w > round(MainCameraComp->Posx) &&
            RenderSize->x < round(MainCameraComp->Posx) + MainCameraComp->screenWidth &&
            RenderSize->y + RenderSize->h > round(MainCameraComp->Posy) &&
            RenderSize->y < round(MainCameraComp->Posy) + MainCameraComp->screenHeight;

        if (!isInViewport)
            continue;

        if (sprite->IsBackGround)
        {
            renderQuad.x = RenderSize->x;
            renderQuad.y = RenderSize->y;
            renderQuad.w = RenderSize->w;
            renderQuad.h = RenderSize->h;

            sprite->Draw(mRenderer, &renderQuad);
#ifdef _DEBUG
            sprite->UpdateDebugRayData();
#endif
        }
        else
        {
            renderQuad.x = RenderSize->x - MainCameraComp->Posx;
            renderQuad.y = RenderSize->y - MainCameraComp->Posy;
            renderQuad.w = RenderSize->w;
            renderQuad.h = RenderSize->h;

            sprite->Draw(mRenderer, &renderQuad);
#ifdef _DEBUG
            sprite->UpdateDebugRayData();
#endif
        }
    }
#ifdef _DEBUG
/*
    for (auto &ray : mRays)
    {
        if (ray->Rectobj != nullptr)
        {
            bool isInViewport =
                ray->Rectobj->GetRect()->x + ray->Rectobj->GetRect()->w > round(MainCameraComp->Posx) &&
                ray->Rectobj->GetRect()->x < round(MainCameraComp->Posx) + MainCameraComp->screenWidth &&
                ray->Rectobj->GetRect()->y + ray->Rectobj->GetRect()->h > round(MainCameraComp->Posy) &&
                ray->Rectobj->GetRect()->y < round(MainCameraComp->Posy) + MainCameraComp->screenHeight;

            if (!isInViewport)
                continue;

            if(ray->Always_On_Camera)
            {
                renderQuad.x = ray->Rectobj->GetRect()->x;
                renderQuad.y = ray->Rectobj->GetRect()->y;
                renderQuad.w = ray->Rectobj->GetRect()->w;
                renderQuad.h = ray->Rectobj->GetRect()->h;
            }else{
            renderQuad.x = ray->Rectobj->GetRect()->x - MainCameraComp->Posx;
            renderQuad.y = ray->Rectobj->GetRect()->y - MainCameraComp->Posy;
            renderQuad.w = ray->Rectobj->GetRect()->w;
            renderQuad.h = ray->Rectobj->GetRect()->h;}
        }
        else if (ray->Lineobj != nullptr)
        {
            renderQuad.x = ray->Lineobj->GetP1().x - MainCameraComp->Posx;
            renderQuad.y = ray->Lineobj->GetP1().y - MainCameraComp->Posy;
            renderQuad.w = ray->Lineobj->GetP2().x - MainCameraComp->Posx;
            renderQuad.h = ray->Lineobj->GetP2().y - MainCameraComp->Posy;
        }

        ray->Draw(mRenderer, &renderQuad);
    }
*/
#endif
    for (auto &text : mTexts)
    {
        RenderSize = text->GetRenderSize();
        renderQuad.x = RenderSize->x;
        renderQuad.y = RenderSize->y;
        renderQuad.w = RenderSize->w;
        renderQuad.h = RenderSize->h;

        text->Draw(mRenderer, &renderQuad);
    }

    SDL_RenderPresent(mRenderer);

    //    SPDLOG_INFO("Sprites {}",mSprites.size());
    //    SPDLOG_INFO("Rays {}",mRays.size());
}

void Renderer::Finalize()
{
    SPDLOG_INFO("??????");
}
Renderer::~Renderer()
{
    SPDLOG_INFO("??????");
}
/// Close Game
void Renderer::Shutdown()
{
    IMG_Quit();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}
