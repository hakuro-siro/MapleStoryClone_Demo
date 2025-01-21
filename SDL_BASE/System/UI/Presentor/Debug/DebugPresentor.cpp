//
// Created by binetsu on 11/26/24.
//
#ifdef _DEBUG
#include "DebugPresentor.h"
#include "System/UI/View/Debug/DebugCanvas.h"
#include "System/Component/FpsCheckComponent.h"
#include "System/Component/MousePositionComponent.h"

DebugPresentor::DebugPresentor():
    Presentor()
{

}

void DebugPresentor::SetCanvas(Canvas& canvas) {
    Presentor::SetCanvas(canvas);
    mDebugCanvas = dynamic_cast<DebugCanvas*>(&canvas);
}

void DebugPresentor::SetEventHandler(FpsCheckComponent& Fpshandler,
                                     MousePositionComponent& Mousehandler) {
    FpsCheckEventHandler = &Fpshandler;
    MousePositionEventHandler = &Mousehandler;
}

void DebugPresentor::BindModelView() {

    auto* obserb1 = new Obserable(
            &FpsCheckEventHandler->FPSCountEvent,
            FpsCheckEventHandler->FPSCountEvent.Subscribe([this](int val)
            { mDebugCanvas->GetTextComp(FPS_TEXT)
            ->SetText(to_string(val),35);  }));

    auto* obserb2 = new Obserable(
            &MousePositionEventHandler->ChangeMousePosEvent,
            MousePositionEventHandler->ChangeMousePosEvent.Subscribe([this](int val)
                      {
                          mDebugCanvas->GetTextComp(MP_TEXT)
                                  ->SetText("Pos : "+
                                          to_string(MousePositionEventHandler->MouseX)
                                          +"/"+
                                              to_string(MousePositionEventHandler->MouseY),35);
                      }));

    Subscribes.emplace_back(obserb1);
    Subscribes.emplace_back(obserb2);


}

DebugPresentor::~DebugPresentor(){

}
#endif