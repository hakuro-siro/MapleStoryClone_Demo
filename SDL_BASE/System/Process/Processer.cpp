
#include "Processer.h"
#include "Renderer.h"
#include "AssetLoader.h"
#include "InputReader.h"
#include "PhysicsProcesser.h"
#include "SDL2/SDL_image.h"
#include <algorithm>
#include "System/GameObject/GameObject.h"
#include "System/TENSHI/Player/Player.h"
#include <vector>
#include "spdlog/spdlog.h"
#ifdef _DEBUG
#include "System/Component/FpsCheckComponent.h"
#include "System/Component/MousePositionComponent.h"
#include "System/UI/Presentor/Debug/DebugPresentor.h"
#include "System/UI/View/Debug/DebugCanvas.h"
#endif

#include "System/Scene/InGameScene.h"
#include "System/Scene/TitleScene.h"
#include "System/Component/TextComponent.h"

// Construct
Processer::Processer()
    : mTicksCount(0), mIsRunning(true)
{
    SPDLOG_INFO("*PROCESSER CONSTRUCTED*");
}

/*
 *  -- Initialize --
 *  Init -> SDL
 *  Create SDL -> Window
 *  Create SDL-> Renderer
 *  Init SDL -> Image
 *  Load Data
 */
bool Processer::Initialize()
{
    RenderProcesser = &Singleton<Renderer>::GetInstance();
    InputReadProcesser = &Singleton<InputReader>::GetInstance();
    AssetLoadProcesser = &Singleton<AssetLoader>::GetInstance();
    physicsProcesser = &Singleton<PhysicsProcesser>::GetInstance();

    for (auto &process : mProcesses)
    {
        if (!process->Initialize())
        {
            SPDLOG_INFO("PROCESSER INITLIZE FAILED!");
            return false;
        }
    }

    auto mScene = new TitleScene();

    SPDLOG_INFO("{}", mScene->SceneData_MASTERDIR);
    if (!AssetLoadProcesser->LoadSceneData(mScene))
        return false;
#ifdef _DEBUG
/*
    auto FPS_Counter = new GameObject();
    FpsChecker = new FpsCheckComponent(FPS_Counter, 10);
    auto MouseChecker = new MousePositionComponent(FPS_Counter, 10);

    DebugCanvas *DebCanvas = new DebugCanvas();
    DebugPresentor *PresentorComp = new DebugPresentor();
    PresentorComp->SetCanvas(*DebCanvas);
    PresentorComp->SetEventHandler(*FpsChecker, *MouseChecker);
    PresentorComp->BindModelView();

    FPS_Counter->Initialize();
    DebCanvas->Initialize();
    PresentorComp->Initialize();
    */
#endif

    return true;
}

// Add GameObject
void Processer::RegisterProcesser(IProcess *process)
{

    // SPDLOG_INFO("RegisterProcesser");
    if (IsUpdateProcess)
    {
        mPendingProcesses.emplace_back(process);
    }
    else
    {
        mProcesses.emplace_back(process);
    }
    // SPDLOG_INFO("Registered Process : {}",(int)mProcesses.size());
}

/// Remove GameObject
void Processer::UnRegisterProcesser(IProcess *process)
{
    // Is it in pending Objects?
    auto iter =
        std::find(mPendingProcesses.begin(), mPendingProcesses.end(), process);
    if (iter != mPendingProcesses.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mPendingProcesses.end() - 1);
        mPendingProcesses.pop_back();
    }
    // Is it in Objects?
    iter = std::find(mProcesses.begin(), mProcesses.end(), process);
    if (iter != mProcesses.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mProcesses.end() - 1);
        mProcesses.pop_back();
    }
}

/// Add GameObject
void Processer::AddGameObject(GameObject *gameObject)
{
    // SPDLOG_INFO("Added GameObject : {}",(int)mGameObjects.size());
    mGameObjects.emplace_back(gameObject);
}

/// Remove GameObject
void Processer::RemoveGameObject(GameObject *gameObject)
{
    // Is it in pending Objects?
    auto iter = std::find(mPendingGameObjects.begin(), mPendingGameObjects.end(), gameObject);
    if (iter != mPendingGameObjects.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mPendingGameObjects.end() - 1);
        mPendingGameObjects.pop_back();
    }
    // Is it in Objects?
    iter = std::find(mGameObjects.begin(), mGameObjects.end(), gameObject);
    if (iter != mGameObjects.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mGameObjects.end() - 1);
        mGameObjects.pop_back();
    }
}

/*
 * Update
 */

void Processer::Update(float deltaTime)
{
    while (mIsRunning)
    {
        UpdateGame();
        RenderProcesser->Render();
    }
}

void Processer::ClearGameObject()
{
    // mGameObjects.back()->SetProcessing(false);
    SceneMoving = true;
    for (auto &obj : mGameObjects)
    {
        obj->SetProcessing(false);
    }
}

void Processer::ReloadScene()
{
    auto mScene = new InGameScene();
    AssetLoadProcesser->LoadSceneData(mScene);
}

/// Update Main Game Logic
void Processer::UpdateGame()
{
    float deltaTime = CalculateDeltaTime();

    /// initlize Process
    for (auto &process : mProcesses)
    {
        if (!process->Initialized)
        {
            process->Initialize();
        }
    }
    /// Update Processes
    IsUpdateProcess = true;
    for (auto &process : mProcesses)
    {
        process->Update(deltaTime);
    }
    for (auto &gameObject : mGameObjects)
    {
        if (!gameObject->Processing)
        {
            gameObject->Finalize();
            DestroyedGameObjects.emplace_back(gameObject);
        }
    }

    for (auto &process : mProcesses)
    {
        if (!process->Processing)
        {
            DestroyedProcesses.emplace_back(process);
        }
    }

    IsUpdateProcess = false;

    /// Add Process
    for (auto &pending : mPendingProcesses)
    {
        mProcesses.emplace_back(pending);
    }
    mPendingProcesses.clear();
    for (auto &pending : mPendingGameObjects)
    {
        mGameObjects.emplace_back(pending);
    }
    mPendingGameObjects.clear();

    for (auto &gameObject : DestroyedGameObjects)
    {
        SPDLOG_INFO("Deleted Object {}", gameObject->GameObjectName);
        RemoveGameObject(gameObject);
    }
    DestroyedGameObjects.clear();

    for (auto &process : DestroyedProcesses)
    {
        process->Finalize();
        UnRegisterProcesser(process);
        delete process;
    }
    DestroyedProcesses.clear();
}

/// DeltaTime Calculate
float Processer::CalculateDeltaTime()
{
#ifdef _DEBUG
/*
    FpsChecker->CurrentTime = SDL_GetTicks();
    */
#endif
    /// DeltaTime Calculate
    // Wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

#ifdef _DEBUG

//    FpsChecker->FPS++;
#endif
    // Clamp maximum delta time value
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    // Update tick counts (for next frame)
    mTicksCount = SDL_GetTicks();
    return deltaTime;
}
/// Close Game
void Processer::Finalize()
{
    // Destroy GameObjects
    while (!mGameObjects.empty())
    {
        delete mGameObjects.back();
    }
    AssetLoadProcesser->UnloadData();
    RenderProcesser->Shutdown();
}
