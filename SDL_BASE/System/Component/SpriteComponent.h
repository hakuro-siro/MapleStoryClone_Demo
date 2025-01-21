//
// Created by binetsu on 8/31/24.
//
#include "Component.h"
#include "SDL2/SDL.h"
#include "System/Utility/Math.h"

#pragma once
class SpriteComponent : public Component{
public:
    //Constructor
    SpriteComponent(class GameObject* owner, int drawOrder = 100);
    ~SpriteComponent();

    void SetTexture(SDL_Texture* texture);
    void SetTexture(SDL_Texture* texture , int Width, int Height);
    void SetTexture(SDL_Texture* texture,SDL_Rect* Range,int PivotX,int PivotY);
    void RefreshTexture();

    void SetFlip(bool flip);
    void SetPosition(Vector2 pos);
    Vector2 GetSpritePosition();
    class Sprite* GetSprite() const { return mSprite; }
    SDL_Texture* currentTexture;
protected:
    class Sprite* mSprite;
};


