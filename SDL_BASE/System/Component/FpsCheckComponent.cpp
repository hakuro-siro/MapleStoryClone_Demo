//
// Created by binetsu on 12/6/24.
//

#ifdef _DEBUG
#include <SDL2/SDL_timer.h>
#include "FpsCheckComponent.h"
#include "spdlog/spdlog.h"
#include "System/Component/Camera/Camera.h"

FpsCheckComponent::FpsCheckComponent(class GameObject *owner, int updateOrder)
        : Component(owner){

}

void FpsCheckComponent::Update(float deltaTime) {
    if(CurrentTime - LastTime >= 1000){
        FPS = FPS/((CurrentTime-LastTime)/1000.0f);
        //SPDLOG_INFO("FPS : {}",FPS);
        LastTime = CurrentTime;
        FPSCountEvent.OnNext(FPS);
        FPS = 0;
    }
}
FpsCheckComponent::~FpsCheckComponent(){

}
#endif