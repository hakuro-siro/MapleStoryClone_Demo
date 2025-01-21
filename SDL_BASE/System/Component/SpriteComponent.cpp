//
// Created by binetsu on 8/31/24.
//

#include "SpriteComponent.h"
#include "System/Process/Sprite.h"
#include "System/GameObject/GameObject.h"
/*
 * SpriteComponent : Component
 */
SpriteComponent::SpriteComponent(GameObject* owner, int drawOrder)
        :Component(owner)
{
    mSprite = new Sprite(owner->GetPosition(),drawOrder);
}

void SpriteComponent::SetTexture(SDL_Texture *texture) {
    mSprite->SetTexture(texture);
    mOwner->SetWidth(mSprite->GetTexWidth());
    mOwner->SetHeight(mSprite->GetTexHeight());
    currentTexture= texture;
}

void SpriteComponent::SetTexture(SDL_Texture *texture, int Width, int Height) {
    mSprite->SetTexture(texture,Width,Height);
    mOwner->SetWidth(mSprite->GetTexWidth());
    mOwner->SetHeight(mSprite->GetTexHeight());
    currentTexture= texture;
}

void SpriteComponent::SetTexture(SDL_Texture *texture, SDL_Rect *Range, int PivotX, int PivotY) {
    mSprite->SetTexture(texture,Range,PivotX,PivotY);
    mOwner->SetWidth(mSprite->GetTexWidth());
    mOwner->SetHeight(mSprite->GetTexHeight());
    currentTexture= texture;
}

void SpriteComponent::SetFlip(bool flip) {
    mSprite->SetFlip(flip);
}
void SpriteComponent::SetPosition(Vector2 pos) {
    mSprite->SetSpritePos(pos);
}

void SpriteComponent::RefreshTexture() {
    mSprite->SetTexture(currentTexture);
}

Vector2 SpriteComponent::GetSpritePosition() {
    return mSprite->GetSpritePos();
}
SpriteComponent::~SpriteComponent()
{
    //SPDLOG_INFO("Delete Sprite");
    delete mSprite;
}