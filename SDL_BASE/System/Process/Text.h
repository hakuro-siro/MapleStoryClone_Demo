#include "SDL2/SDL.h"
#include "System/Utility/Math.h"

#pragma once
class Text {

public:
    //Constructor
    Text(Vector2 TextPosition,int drawOrder = 110);
    ~Text();

    //functions
    virtual void Draw(SDL_Renderer* renderer,SDL_Rect* CameraRange);
    virtual void SetTexture(SDL_Texture* texture);

    /// Getter
    int GetDrawOrder() const { return mDrawOrder; }
    void SetSpritePos(Vector2 Pos) { SpritePos = Pos;}
    SDL_Rect* GetRenderSize() { return &RenderSize; }
    /// 가져온 범위의 실제 렌더 크기
    void SetRenderSize(int w,int h,int x,int y) {
        RenderSize.x = x;
        RenderSize.y = y;
        RenderSize.w = w;
        RenderSize.h = h;
    };
protected:
    Vector2 SpritePos = Vector2::Zero;
    SDL_Texture* mTexture;
    SDL_Rect RenderSize;
    int mDrawOrder;
    int mTexHeight;
    int mTexWidth;
};


