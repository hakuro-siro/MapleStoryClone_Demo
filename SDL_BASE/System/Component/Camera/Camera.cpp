#include <iostream>
#include "Camera.h"
#include "System/GameObject/GameObject.h"
#include "System/Utility/DebugRay.h"
Camera::Camera(GameObject *owner, int updateOrder, int x, int y, int w, int h)
    : Component(owner),
      Posx(x),
      Posy(y),
      MinLimitX(0),
      MinLimitY(100),
      MaxLimitX(2200),
      MaxLimitY(0),
      screenWidth(w),
      screenHeight(h),
      Target(nullptr)
{
    // owner->SetPosition(Vector2(Posx,Posy));
}

void Camera::Update(float deltaTime)
{
    //    if(CamerRangeDebugRay== nullptr){
    //        CamerRangeDebugRay = new DebugRay();
    //        CamerRangeDebugRay->CreateRayObject(Posx,Posy,screenWidth,screenHeight,Bcolor);

    //}
    UpdateCameraPos(deltaTime);
    // CamerRangeDebugRay->CreateRayObject(Posx,Posy,screenWidth,screenHeight,Bcolor);
}

void Camera::UpdateCameraPos(float deltaTime)
{
    if (Target == nullptr)
        return;
    Posx = (Target->GetPosition().x - (screenWidth / 2));
    Posy = (Target->GetPosition().y - (screenHeight / 2));
    if (Posx < MinLimitX)
        Posx = MinLimitX;
    if (Posy > MinLimitY)
        Posy = MinLimitY;
    if (Posx > MaxLimitX)
        Posx = MaxLimitX;
    if (Posy < MaxLimitY)
        Posy = MaxLimitY;
    // std::cout<<Posx<<"/"<<Posy<<std::endl;
}