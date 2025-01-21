//
// Created by binetsu on 11/23/24.
//
#include "Text.h"
#include "Renderer.h"

Text::Text(Vector2 TextPosition, int drawOrder) {
    Singleton<Renderer>::GetInstance().AddText(this);
    SpritePos=TextPosition;
}

void Text::SetTexture(SDL_Texture *texture) {
    mTexture = texture;
    SDL_QueryTexture(texture, nullptr, nullptr,&mTexWidth,&mTexHeight);
    SetRenderSize(
            mTexWidth,
            mTexHeight,
            SpritePos.x - mTexWidth/2,
            SpritePos.y - mTexHeight/2);
}

void Text::Draw(SDL_Renderer *renderer, SDL_Rect *CameraRange) {
    if(mTexture){
        SDL_RenderCopyEx(renderer,
                             mTexture,
                             NULL,
                             CameraRange,
                             0,
                             nullptr,
                             SDL_FLIP_NONE);
    }
}
Text::~Text() {
    Singleton<Renderer>::GetInstance().RemoveText(this);
}