//
// Created by binetsu on 9/11/24.
//

#ifdef _DEBUG
#include "DebugRay.h"
#include "../GameObject/GameObject.h"
#include "../Process/Renderer.h"

DebugRay::DebugRay(){
    Singleton<Renderer>::GetInstance().AddDebugRay(this);
}

void DebugRay::CreateLineRayObject(Vector2* P1, Vector2* P2, RayColor* color) {
    Lineobj = new LineRayObject(P1,P2,color);
}
void DebugRay::CreateRayObject(int x, int y, int w, int h, RayColor* color) {
    Rectobj = new RayObject(x,y,w,h,color);
}


DebugRay::~DebugRay() {
    Singleton<Renderer>::GetInstance().RemoveDebugRay(this);
    delete Rectobj;
}

void DebugRay::Draw(SDL_Renderer *renderer,SDL_Rect* CameraRange) {


    if (Rectobj != nullptr) {
        SDL_SetRenderDrawColor(renderer,
                               Rectobj->GetColor()->R,
                               Rectobj->GetColor()->G,
                               Rectobj->GetColor()->B,
                               Rectobj->GetColor()->A);
        SDL_RenderDrawRect(renderer, CameraRange);
    }
    if (Lineobj != nullptr) {
        SDL_SetRenderDrawColor(renderer,
                               Lineobj->GetColor()->R,
                               Lineobj->GetColor()->G,
                               Lineobj->GetColor()->B,
                               Lineobj->GetColor()->A);
        SDL_RenderDrawLine(renderer,
                           CameraRange->x, CameraRange->y,
                           CameraRange->w, CameraRange->h);
    }
}


RayObject::RayObject(int x,int y,int w, int h , RayColor* color) :
    Color(color)
    {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
    }

RayObject::~RayObject() { }

LineRayObject::LineRayObject(Vector2 *p1, Vector2 *p2, RayColor* color):
    Color(color)
    {
        P1.x = p1->x;
        P1.y = p1->y;
        P2.x = p2->x;
        P2.y = p2->y;
    }

LineRayObject::~LineRayObject() { delete Color; }

#endif