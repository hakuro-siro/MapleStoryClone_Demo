//
// Created by binetsu on 11/26/24.
//
#ifdef _DEBUG
#include "DebugCanvas.h"

DebugCanvas::DebugCanvas():
Canvas()
{
}

bool DebugCanvas::Initialize() {
    GameObject::Initialize();

    auto FPS_Text = new GameObject();
    FPS_Text->SetPosition(Vector2(50,50));
    TextComponent* FpsTexComp = new TextComponent(FPS_Text,100);
    FpsTexComp->SetFont(NEXON_GOTHIC_MEDIUM);
    FpsTexComp->SetText("FPS : 00",35);

    auto MousePosition_Text = new GameObject();
    MousePosition_Text->SetPosition(Vector2(300,50));
    TextComponent* MP_TexComp = new TextComponent(MousePosition_Text,100);
    MP_TexComp->SetFont(NEXON_GOTHIC_MEDIUM);
    MP_TexComp->SetText("MousePos (X.Y)",35);

    FPS_Text->Initialize();
    MousePosition_Text->Initialize();

    AddTextComp(FPS_TEXT,FpsTexComp);
    AddTextComp(MP_TEXT,MP_TexComp);


    return true;
}


DebugCanvas::~DebugCanvas()
{

}
#endif