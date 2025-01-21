//
// Created by binetsu on 11/26/24.
//

#include "TitleCanvas.h"
#include "System/Process/Processer.h"
#include "System/Process/AssetLoader.h"
#include "System/Process/InputReader.h"
#include "System/Utility/Event.h"
#include "System/Scene/InGameScene.h"

TitleCanvas::TitleCanvas():
        Canvas()
{
}

bool TitleCanvas::Initialize() {
    GameObject::Initialize();

    auto Title_Text = new GameObject();
    Title_Text->SetPosition(Vector2(700,300));
    TextComponent* TitleTexComp = new TextComponent(Title_Text,100);
    TitleTexComp->SetFont(NEXON_GOTHIC_MEDIUM);
    TitleTexComp->SetText("MapleStory",100,0,0,0);
    auto Title_Tex2 = new GameObject();
    Title_Tex2->SetPosition(Vector2(710,300));
    TextComponent* TitleTexComp2 = new TextComponent(Title_Tex2,100);
    TitleTexComp2->SetFont(NEXON_GOTHIC_MEDIUM);
    TitleTexComp2->SetText("MapleStory",100,255,255,255);

    auto Start_Text = new GameObject();
    Start_Text->SetPosition(Vector2(700,500));
    TextComponent* StartTexComp = new TextComponent(Start_Text,100);
    StartTexComp->SetFont(NEXON_GOTHIC_MEDIUM);
    StartTexComp->SetText("Press Spacebar",40);

    Title_Text->Initialize();
    Title_Tex2->Initialize();
    Start_Text->Initialize();

    AddTextComp(START_TEXT,StartTexComp);
    AddTextComp(TITLE_TEXT,TitleTexComp);
    AddTextComp(TITL2_TEXT,TitleTexComp2);

    auto* GameStartEvent = new Obserable(
            &Singleton<InputReader>::GetInstance().GameStartEvent,
            Singleton<InputReader>::GetInstance().GameStartEvent.Subscribe([this](int){
                gotoIngame();}));


    Subscribes.emplace_back(GameStartEvent);
    return true;
}

void TitleCanvas::gotoIngame() {
    for (auto &observe: Subscribes) {
        observe->event->UnSubscribe(observe->key);
    }
    Subscribes.clear();

    GetTextComp(TITLE_TEXT)->GetOwner()->SetProcessing(false);
    GetTextComp(TITL2_TEXT)->GetOwner()->SetProcessing(false);
    GetTextComp(START_TEXT)->GetOwner()->SetProcessing(false);

    Singleton<Processer>::GetInstance().ClearGameObject();
    Singleton<AssetLoader>::GetInstance().CurrentScene = new InGameScene();
    Singleton<AssetLoader>::GetInstance().GoPortalInGameMap();
}


TitleCanvas::~TitleCanvas()
{

}
