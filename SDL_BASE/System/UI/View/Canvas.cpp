//
// Created by binetsu on 11/23/24.
//

#include "Canvas.h"
#include "System/Process/Renderer.h"


Canvas::Canvas():
GameObject(){
    mWidth = WINDOW_WIDTH;
    mHeight = WINDOW_HEIGHT;
#ifdef _DEBUG
    CanvasdebugRay = new DebugRay();
    CanvasdebugRay->Always_On_Camera = true;
    CanvasdebugRay->CreateRayObject(
            mPosition.x,mPosition.y,mWidth-10,mHeight-10,Bcolor);
 #endif
}

Canvas::~Canvas() {

}