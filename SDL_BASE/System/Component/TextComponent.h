//
// Created by binetsu on 8/31/24.
//
#include <string>
#include "Component.h"
#include "SDL2/SDL.h"
#include "System/Utility/Math.h"
#include "System/Data/AssetPath.h"

enum Anchor{
    Center,
    LeftTop,
    RightTop,
    LeftCenter,
    RightCenter,
    LeftBottom,
    RightBottom,
};

#pragma once
class TextComponent : public Component{
public:
    //Constructor
    TextComponent(class GameObject* owner, int drawOrder = 110 ,std::string FontName = NEXON_GOTHIC_MEDIUM);
    void SetPosition(Vector2 pos);
    void SetTexture(SDL_Texture *texture);
    void SetAnchor(Anchor anchor);
    ~TextComponent();
    void SetText(std::string Text,int Size);
    void SetText(std::string Text,int Size,int R,int G,int B);
        void SetFont(std::string FontName) { mFont = FontName; }
protected:
    class Text* mText;
    std::string mFont;
    Anchor mAnchor = Anchor::Center;
};


