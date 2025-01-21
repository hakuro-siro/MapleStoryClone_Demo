
#pragma once
#include "System/Component/Component.h"

class Camera : public Component {

public:
    Camera(class GameObject* owner, int updateOrder = 10,
            int x = 0,
            int y = 0,
            int w = 0,
            int h = 0);
    void FollowThis(class GameObject* target){
        Target = target;
    }
    void ForgetMe(){
        Target = nullptr;
    }
    void Update(float deltaTime) override;
    void UpdateCameraPos(float deltaTime);
    float Posx, Posy;
    float MinLimitX,MinLimitY;
    float MaxLimitX,MaxLimitY;
    int screenWidth, screenHeight;
    class GameObject* Target;
    class DebugRay* CamerRangeDebugRay;
    };
