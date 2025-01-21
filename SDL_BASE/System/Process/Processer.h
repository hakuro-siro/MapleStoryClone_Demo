// ----------------------------------------------------------------
// SDL BASE - PROCESS
// ----------------------------------------------------------------

#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>
#include "System/Utility/Singleton.h"
#include "System/Process/IProcess.h"
// Game class
class Processer : Singleton<Processer>
{
public:
	Processer();
	// Initialize
    bool Initialize();
	// Loop 의사적 Update
	void Update(float deltaTime);
	// Finalize
    void Finalize();

    // Register Proceser
    void RegisterProcesser(IProcess* process);
    // UnRegister Processer
    void UnRegisterProcesser(IProcess* process);

    // Add GameObject
    void AddGameObject(class GameObject* gameObject);
    // Delete GameObject
    void RemoveGameObject(class GameObject* gameObject);

    /// Getter
    std::vector<class GameObject*> GetGameObjects() const {return mGameObjects;}
    std::vector<class GameObject*> GetPendingGameObjects() const {return mPendingGameObjects;}
    class Renderer* GetRenderer() const { return RenderProcesser;}
    class AssetLoader* GetAssetLoader() const { return  AssetLoadProcesser; }
    class InputReader* GetInputReader() const { return InputReadProcesser; }
    class PhysicsProcesser* GetPhysicsProcesser() const { return physicsProcesser; }

    /// Setter
    void SetIsRunning(bool isrunning) { mIsRunning = isrunning; }
    void ClearGameObject();
    void ReloadScene();

#ifdef _DEBUG
    class FpsCheckComponent* FpsChecker;
#endif

    bool SceneMoving = false;
private:
    class PhysicsProcesser* physicsProcesser;
    class Renderer* RenderProcesser;
    class AssetLoader* AssetLoadProcesser;
    class InputReader* InputReadProcesser;
    // input
	void ProcessInput();
    // update
	void UpdateGame();
    //Calculate Tick
    float CalculateDeltaTime();
	// TICK
	Uint32 mTicksCount;

    /// Vector of Process
    std::vector<class IProcess*> mProcesses;
    std::vector<class IProcess*> mPendingProcesses;
    std::vector<class IProcess*> DestroyedProcesses;

    // Vector of GameObjects
    std::vector<class GameObject*> mGameObjects;
    std::vector<class GameObject*> mPendingGameObjects;
    std::vector<GameObject*> DestroyedGameObjects;

    // Running?
	bool mIsRunning = false;
    // Update GameObjects
    bool mUpdatingObjects = false;
    // Update Process
    bool IsUpdateProcess = false;

    class Scene* CurrentScene;
    // Game-specific
    class Player* mPlayer;
};
