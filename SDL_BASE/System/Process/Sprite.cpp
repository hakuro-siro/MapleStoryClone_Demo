//
// Created by binetsu on 8/31/24.
//

#include <iostream>
#include "Sprite.h"
#include "System/GameObject/GameObject.h"
#include "System/Process/Renderer.h"

#ifdef _DEBUG
#include "System/Utility/DebugRay.h"
#endif
/*
 * SpriteComponent : Component
 */
Sprite::Sprite(Vector2 spritePositon,int drawOrder)
        :mTexture(nullptr)
        ,mDrawOrder(drawOrder)
        ,mTexWidth(0)
        ,mTexHeight(0)
        ,SpritePos(spritePositon)
{
    Singleton<Renderer>::GetInstance().AddSprite(this);

#ifdef _DEBUG
    SpritedebugRay = new DebugRay();
    CenterdebugRay = new DebugRay();

    SpritedebugRay->CreateRayObject(RenderSize.x,RenderSize.y,RenderSize.w,RenderSize.h,Bcolor);
    CenterdebugRay->CreateRayObject(SpritePos.x-5,SpritePos.y-5,10,10,Gcolor);
#endif

}

Sprite::~Sprite()
{
    Singleton<Renderer>::GetInstance().RemoveSprite(this);
#ifdef _DEBUG
    delete SpritedebugRay;

    delete CenterdebugRay;
#endif
}

/// Set Texture
void Sprite::SetTexture(SDL_Texture *texture) {
    mTexture = texture;

    SDL_QueryTexture(texture, nullptr, nullptr,&mTexWidth,&mTexHeight);

    Pivotx = mTexWidth/2;
    SetRenderRange(
            mTexWidth,
            mTexHeight,
            0,
            0);
    SetRenderSize(
            mTexWidth,
            mTexHeight,
            SpritePos.x - mTexWidth/2,
            SpritePos.y - mTexHeight/2);
}

void Sprite::SetTexture(SDL_Texture *texture, int Width, int Height) {

    mTexture = texture;

    int FixedXpos = 0;
    int FixedYpos = 0;
    int FixedWidth = Width;
    int FixedHeight = Height;

    SDL_QueryTexture(texture, nullptr, nullptr,&mTexWidth,&mTexHeight);

    if(mTexWidth<Width){
        FixedXpos = Width- mTexWidth;

        FixedWidth = mTexWidth;
        FixedHeight = mTexHeight;
    }
    if(mTexHeight<Height){
        FixedYpos = Height-mTexHeight;

        FixedWidth = mTexWidth;
        FixedHeight = mTexHeight;
    }

    SetRenderRange(
            mTexWidth,
            mTexHeight,
            0,
            0);
    SetRenderSize(
            FixedWidth,
            FixedHeight,
            (SpritePos.x - Width/2)+FixedXpos,
            (SpritePos.y - Height/2)+FixedYpos);
}

/// Set Texture By Range
void Sprite::SetTexture(SDL_Texture *texture,SDL_Rect* Range,int PivotX,int PivotY){

    mTexture = texture;
    Pivotx = PivotX;

    SetRenderSize(
            Range->w,
            Range->h,
            SpritePos.x - PivotX,
            SpritePos.y - PivotY);

    RenderRange = *Range;

}

#ifdef _DEBUG
void Sprite::UpdateDebugRayData() {
    SpritedebugRay->UpdateRayObject(RenderSize.x,RenderSize.y,RenderSize.w,RenderSize.h);
    CenterdebugRay->UpdateRayObject(SpritePos.x-5,SpritePos.y-5,10,10);
}
#endif

/// Render Copy
void Sprite::Draw(SDL_Renderer *renderer,SDL_Rect* CameraRange) {
    if(mTexture){
        if(!Flip){
            SDL_RenderCopyEx(renderer,
                             mTexture,
                             &RenderRange,
                             CameraRange,
                             0,
                             nullptr,
                             SDL_FLIP_NONE);
        }
        else
        {
            RenderSize.x = SpritePos.x + (Pivotx - RenderSize.w);
            CameraRange->x = RenderSize.x - Singleton<Renderer>::GetInstance().MainCameraComp->Posx;

            SDL_RenderCopyEx(renderer,
                             mTexture,
                             &RenderRange,
                             CameraRange,
                             0,
                             nullptr,
                             SDL_FLIP_HORIZONTAL);
        }
    }
}