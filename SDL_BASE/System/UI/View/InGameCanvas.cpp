//
// Created by binetsu on 11/26/24.
//

#include "InGameCanvas.h"

InGameCanvas::InGameCanvas():
        Canvas()
{
}

bool InGameCanvas::Initialize() {
    GameObject::Initialize();
    return true;
}


InGameCanvas::~InGameCanvas()
{

}
