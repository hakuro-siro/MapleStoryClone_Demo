//
// Created by binetsu on 12/7/24.
//
#ifdef _DEBUG
#include <SDL2/SDL_mouse.h>
#include "MousePositionComponent.h"
#include "System/Utility/Singleton.h"
#include "System/Process/Renderer.h"

MousePositionComponent::MousePositionComponent(class GameObject *owner, int updateOrder)
        :Component(owner){

}

void MousePositionComponent::Update(float deltaTime) {

    SDL_GetMouseState(&MouseX,&MouseY);
    MouseX = Singleton<Renderer>::GetInstance().MainCameraComp->Posx + MouseX;
    MouseY = Singleton<Renderer>::GetInstance().MainCameraComp->Posy + MouseY;

    if(MouseXBuf!=MouseX)
    {

        MouseXBuf = MouseX;
        ChangeMousePosEvent.OnNext(1);
    }
    if(MouseYBuf!=MouseY){
        MouseYBuf = MouseY;
        ChangeMousePosEvent.OnNext(1);
    }
}
MousePositionComponent::~MousePositionComponent() noexcept {

}
#endif
