//
// Created by binetsu on 8/31/24.
//
#pragma once
#include "SpriteComponent.h"
#include "System/Data/AnimSpriteData.h"
#include "System/Utility/Event.h"
#include <vector>

class AnimSpriteComponent : public SpriteComponent {

public:
    /// Construct
    AnimSpriteComponent(class GameObject* owner, int drawOrder = 100);
    ~AnimSpriteComponent();
    void Update(float deltaTime) override;

    void SetAniTextures(SDL_Texture& texture, vector<AnimSpriteData> data);
    void SetAniTextures(vector<SDL_Texture*> textures);

    /// Getter - Setter
    float GetAnimFps() const { return mAnimFPS; }
    bool LoopFlag = true;
    bool StopAnimationFlag = false;
    bool Killflag = false;
    Event<int> AnimationFinishEvent;
    Event<int> AnimationEvent;
    int AnimationEventFrame = 0;

    void SetAnimFPS(float fps) { mAnimFPS = fps; }
    void ClearSprites();
private:
    std::vector<SDL_Rect*> mAnimTextureRanges;
    SDL_Texture * mAnimTexture;
    std::vector<SDL_Texture*> mAnimTextureSep;
    float mCurrFrame;
    float mAnimFPS;
    int PivotX;
    int PivotY;
};