//
// Created by binetsu on 11/26/24.
//

#include <vector>
#include "System/Utility/Singleton.h"
#include "IProcess.h"
#include "System/Scene/Scene.h"

enum Scene_Code{
    TEST_SCENE,
    TITLE_SCENE
};
class SceneManager : IProcess ,Singleton<SceneManager>{

public:
    //Construct
    SceneManager();
    ~SceneManager();
    bool Initialize() override;
    void Finalize() override;

    void ChangeScene(Scene_Code SceneCode);

    Scene* CurrentScene;
};
