//
// Created by binetsu on 8/31/24.
//

/// Animation Sprite Component
#include "AnimSpriteComponent.h"
#include "System/Process/Sprite.h"
#include "System/GameObject/GameObject.h"
/// Constructor

AnimSpriteComponent::AnimSpriteComponent(GameObject* owner, int drawOrder) :
    SpriteComponent(owner, drawOrder)
    , mCurrFrame(0.0f)
    , mAnimFPS(24.0f)
    {
    }

    /// Component Update
    void AnimSpriteComponent::Update(float deltaTime) {

        SpriteComponent::Update(deltaTime);
        if(StopAnimationFlag){
            return;
        }
        // Render Sprites For Frames
        if(mAnimTextureRanges.size() > 0){

            mCurrFrame += mAnimFPS * deltaTime;

            while(mCurrFrame >= mAnimTextureRanges.size()){
                if(LoopFlag)
                    mCurrFrame -=mAnimTextureRanges.size();
                else{
                    AnimationFinishEvent.OnNext(0);
                    StopAnimationFlag = true;
                    return;
                }
            }

            if((static_cast<int>(mCurrFrame)==AnimationEventFrame)&&
            AnimationEventFrame!=0)
                AnimationEvent.OnNext(0);
            SetPosition(mOwner->GetPosition());
            mSprite->SetTexture(
                    mAnimTexture,
                    mAnimTextureRanges[static_cast<int>(mCurrFrame)],
                    PivotX,
                    PivotY);
        }
        if(mAnimTextureSep.size() > 0){

            mCurrFrame += mAnimFPS * deltaTime;

            while(mCurrFrame >= mAnimTextureSep.size()){
                if(LoopFlag)
                    mCurrFrame -=mAnimTextureSep.size();
                else{
                    AnimationFinishEvent.OnNext(0);
                    StopAnimationFlag = true;

                    if(Killflag){
                        mOwner->SetProcessing(false);
                    }
                    return;
                }
            }


            if((static_cast<int>(mCurrFrame)==AnimationEventFrame)&&
               AnimationEventFrame!=0)
                AnimationEvent.OnNext(0);

            SetPosition(mOwner->GetPosition());
            mSprite->SetTexture(mAnimTextureSep[mCurrFrame]);
        }

    }

    // Set Animation Texture
    void AnimSpriteComponent::SetAniTextures(SDL_Texture& texture,vector<AnimSpriteData> data)
    {
        mAnimTexture = &texture;
        mAnimTextureRanges.clear();
        for (auto& animsprite : data) {
            SDL_Rect* rect = new SDL_Rect();
            rect->x = animsprite.X;
            rect->y = animsprite.Y;
            rect->h = animsprite.Height;
            rect->w = animsprite.Width;
            PivotX = animsprite.PivotX;
            PivotY = animsprite.PivotY;
            mAnimTextureRanges.push_back(rect);
        }
        if (!mAnimTextureRanges.empty())
        {
            // Set the active texture to first frame
            mCurrFrame = 0.0f;
            mSprite->SetTexture(mAnimTexture,mAnimTextureRanges[0],PivotX,PivotY);
            mOwner->SetWidth(mAnimTextureRanges[0]->w);
            mOwner->SetHeight(mAnimTextureRanges[0]->h);
        }
}

void AnimSpriteComponent::ClearSprites() {
    mAnimTextureRanges.clear();
    mAnimTextureSep.clear();
    mSprite->SetTexture(nullptr);
}
void AnimSpriteComponent::SetAniTextures(vector<SDL_Texture*> textures)
{
    mAnimTextureSep = textures;
    mCurrFrame = 0.0f;
    mSprite->SetTexture(mAnimTextureSep[0]);
    //mOwner->SetWidth(mSprite->GetTexWidth());
    //mOwner->SetHeight(mSprite->GetTexHeight());
}
AnimSpriteComponent::~AnimSpriteComponent()
{
}