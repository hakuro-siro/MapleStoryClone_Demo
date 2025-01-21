//
// Created by binetsu on 9/11/24.
//

#ifdef _DEBUG
#include "../Component/Component.h"
#include "Math.h"
#include "SDL2/SDL.h"
#include <vector>


struct RayColor {
    RayColor(int r, int g, int b, int a) {
        R = r;
        G = g;
        B = b;
        A = a;
    }

    int R;
    int G;
    int B;
    int A;
};

class RayObject {
public:
    RayObject(int x,int y,int w, int h ,RayColor* color);

    ~RayObject();

    /// Setter
    void SetRect(int x,int y,int w,int h) { rect.x = x; rect.y = y; rect.w = w; rect.h = h;}
    /// Getter
    SDL_Rect* GetRect() { return &rect; }
    RayColor* GetColor() const {return Color;}

private:
    SDL_Rect rect;
    RayColor* Color;
};

class LineRayObject {
public:
    LineRayObject(Vector2 *p1, Vector2 *p2, RayColor* color);

    ~LineRayObject();

    ///Setter
    void SetP1(Vector2* pos) { P1.x = pos->x , P1.y = pos->y;}
    void SetP2(Vector2* pos) { P2.x = pos->x , P2.y = pos->y;}
    ///Getter
    SDL_Point GetP1() const {return P1;}
    SDL_Point GetP2() const {return P2;}
    RayColor* GetColor() const {return Color;}
private:
    SDL_Point P1;
    SDL_Point P2;
    RayColor* Color;
};

static RayColor* Gcolor = new RayColor(0, 255, 0, 255);
static RayColor* Rcolor = new RayColor(255,0,0,255);
static RayColor* Bcolor = new RayColor(0,0,255,255);

class DebugRay {

public:
    DebugRay();

    ~DebugRay();

    void CreateLineRayObject(Vector2* P1, Vector2* P2, RayColor* color);

    void CreateRayObject(int x, int y, int w, int h, RayColor* color);

    void UpdateRayObject(int x, int y, int w, int h) {
        Rectobj->SetRect(x,y,w,h);
    }

    void UpdateLineRayObject(Vector2 *P1, Vector2 *P2) {
        Lineobj->SetP1(P1);
        Lineobj->SetP2(P2);
    }

    void Draw(SDL_Renderer *renderer,SDL_Rect* CameraRange);

    RayObject *Rectobj = nullptr;
    LineRayObject *Lineobj = nullptr;
    bool Always_On_Camera = false;
};
#endif