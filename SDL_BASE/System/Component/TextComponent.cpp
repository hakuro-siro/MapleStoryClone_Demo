//
// Created by binetsu on 8/31/24.
//

#include "TextComponent.h"
#include "System/Process/Sprite.h"
#include "System/GameObject/GameObject.h"
#include "System/Process/Text.h"
#include "System/Process/AssetLoader.h"

/*
 * TextComponent : Component
 */
TextComponent::TextComponent(GameObject* owner, int drawOrder ,std::string FontName)
        :Component(owner),
         mFont(FontName)
{
    mText = new Text(owner->GetPosition(),drawOrder);
}

void TextComponent::SetText(std::string Text,int Size) {
    SetTexture(Singleton<AssetLoader>::GetInstance().GetText(Text,mFont,Size));
}
void TextComponent::SetText(std::string Text,int Size,int R,int G,int B) {
    SetTexture(Singleton<AssetLoader>::GetInstance().GetText(Text,mFont,Size,R,G,B));
}
void TextComponent::SetTexture(SDL_Texture *texture) {
    mText->SetTexture(texture);
}

void TextComponent::SetPosition(Vector2 pos) {
    Vector2 AnchorPos = pos;
    Vector2 FixPos = Vector2::Zero;
    switch(mAnchor){
        case Anchor::Center:
            AnchorPos = pos;
        case Anchor::LeftTop:
            AnchorPos = Vector2(pos.x - mOwner->GetWidth()/2,
                             pos.y - mOwner->GetHeight()/2);
        case Anchor::LeftBottom:
            AnchorPos = Vector2(pos.x - mOwner->GetWidth()/2,
                                pos.y + mOwner->GetHeight()/2);
        case Anchor::LeftCenter:
            AnchorPos = Vector2(pos.x - mOwner->GetWidth()/2,
                                pos.y);
        case Anchor::RightTop:
            AnchorPos = Vector2(pos.x + mOwner->GetWidth()/2,
                                pos.y - mOwner->GetHeight()/2);
        case Anchor::RightBottom:
            AnchorPos = Vector2(pos.x - mOwner->GetWidth()/2,
                                pos.y + mOwner->GetHeight()/2);
        case Anchor::RightCenter:
            AnchorPos = Vector2(pos.x - mOwner->GetWidth()/2,
                                pos.y);
    }
    mText->SetSpritePos(AnchorPos);
}

TextComponent::~TextComponent()
{
    delete mText;
    SPDLOG_INFO("Delete Text");
}