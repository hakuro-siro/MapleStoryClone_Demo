//
// Created by binetsu on 12/14/24.
//

#include "Damage.h"
#include "System/GameObject/GameObject.h"
#include "System/Process/AssetLoader.h"

Damage::Damage(GameObject* obj)
{
    DamageObject = obj;
    //SPDLOG_INFO("Active Dmg");
}
int Xpos = 30;
// 최대 99999
void Damage::SetDamage(int dmg){
    if(dmg>=10000)
    {
        DamageNumbers.emplace_back(Get10000(dmg));
        DamageNumbers.emplace_back(Get1000(dmg));
        DamageNumbers.emplace_back(Get100(dmg));
        DamageNumbers.emplace_back(Get10(dmg));
        DamageNumbers.emplace_back(GetP1(dmg));

    }
    else if(dmg>=1000){
        DamageNumbers.emplace_back(Get1000(dmg));
        DamageNumbers.emplace_back(Get100(dmg));
        DamageNumbers.emplace_back(Get10(dmg));
        DamageNumbers.emplace_back(GetP1(dmg));
    }
    else if(dmg>=100){
        DamageNumbers.emplace_back(Get100(dmg));
        DamageNumbers.emplace_back(Get10(dmg));
        DamageNumbers.emplace_back(GetP1(dmg));
    }
    else if(dmg>=10){
        DamageNumbers.emplace_back(Get10(dmg));
        DamageNumbers.emplace_back(GetP1(dmg));
    }
    else
    {
        DamageNumbers.emplace_back(GetP1(dmg));
    }

    for(auto number : DamageNumbers){
        DamageTextures.emplace_back(
                Singleton<AssetLoader>::GetInstance().GetTexture(
                        DAMAGE_DIR+DamageNumMap
                                .at(number)));
    }
    int order = 130;
    for(auto tex : DamageTextures){
        SpriteComponent* dmgimg
            = new SpriteComponent(DamageObject,order);
        order--;
        dmgimg->SetTexture(tex);
        DamageObject->SetPosition(
                Vector2(
                DamageObject->GetPosition().x+Xpos,
                DamageObject->GetPosition().y
                )
                );
        DamageTextureComponents.emplace_back(dmgimg);
    }
}

void Damage::UpdateDamageLifeTime(float deltaTime) {
    CurrentLifeTime+=deltaTime;
    DamageObject->SetPosition(
            Vector2(
                    DamageObject->GetPosition().x,
                    DamageObject->GetPosition().y-5
            )
    );
    for(auto comp : DamageTextureComponents){
        comp->SetPosition(
                Vector2(
                        comp->GetSpritePosition().x,
                        DamageObject->GetPosition().y
                ));
        comp->RefreshTexture();
    }
    //SPDLOG_INFO("Active Time {}",CurrentLifeTime);
}

Damage::~Damage(){
    SPDLOG_INFO("Delete Dmg");
    DamageObject->SetProcessing(false);
}