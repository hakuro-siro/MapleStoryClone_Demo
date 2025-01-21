#include "SDL2/SDL.h"
#include "System/Utility/Math.h"

#pragma once
class Sprite {

public:
    bool IsBackGround = false;
    //Constructor
    Sprite(Vector2 spritePosition,int drawOrder = 100);
    ~Sprite();

    //functions
    virtual void Draw(SDL_Renderer* renderer,SDL_Rect* CameraRange);

#ifdef _DEBUG
    virtual void UpdateDebugRayData();
#endif
    /// Getter
    int GetDrawOrder() const { return mDrawOrder; }
    int GetTexHeight() const { return mTexHeight; }
    int GetTexWidth() const { return mTexWidth;}
    SDL_Rect* GetRenderSize() { return &RenderSize; }

    Vector2 GetSpritePos(){return SpritePos;}
    void SetSpritePos(Vector2 Pos) { SpritePos = Pos;}

    void SetFlip(bool flip) { Flip = flip; }

    void SetTexture(SDL_Texture* texture);
    void SetTexture(SDL_Texture* texture , int Width, int Height);
    void SetTexture(SDL_Texture* texture,SDL_Rect* Range,int PivotX,int PivotY);

protected:
    Vector2 SpritePos = Vector2::Zero;
    bool Flip = false;
#ifdef _DEBUG
    class DebugRay* SpritedebugRay;
    class DebugRay* CenterdebugRay;
#endif

    /// Sprite 에서 가져올 범위
    void SetRenderRange(int w,int h,int x,int y) {
        RenderRange.x = x;
        RenderRange.y = y;
        RenderRange.w = w;
        RenderRange.h = h;
    };
    /// 가져온 범위의 실제 렌더 크기
    void SetRenderSize(int w,int h,int x,int y) {
        RenderSize.x = x;
        RenderSize.y = y;
        RenderSize.w = w;
        RenderSize.h = h;
    };
    SDL_Texture* mTexture;
    SDL_Rect RenderSize;
    SDL_Rect RenderRange;
    SDL_Point point;

    int mDrawOrder;
    int mTexHeight;
    int mTexWidth;

    int Pivotx = 0;
};


