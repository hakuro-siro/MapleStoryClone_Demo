
//
// Created by binetsu on 9/4/24.
//
#include <SDL2/SDL.h>
#include "PlayerSkillState.h"
#include "System/GameObject/GameObject.h"
#include "System/Utility/Math.h"
#include "System/Process/Processer.h"
#include "System/Process/InputReader.h"
#include "Player.h"
#include "System/Data/AnimSpriteData.h"
#include "System/Data/AssetPath.h"
#include "System/Process/AssetLoader.h"
#include "System/Component/AnimSpriteComponent.h"
#include "System/Component/FSM/StateMachine.h"
#include "PlayerIdleState.h"
#include "System/Physics/Rigidbody.h"
#include "System/Physics/BoxCollider.h"
#include "System/Physics/LineCollider.h"
#include "spdlog/spdlog.h"
#include "PlayerMoveState.h"
#include "System/Process/Sprite.h"
#include "System/RayCast/RayCastObject.h"
#include "System/TENSHI/Damage/Health.h"
#ifdef _DEBUG
#include "System/Utility/DebugRay.h"
#endif
PlayerSkillState::PlayerSkillState(Player * player,StateMachine* machine, string SkillCode)
        :PlayerState()
        {
            mMachine = machine;
            mPlayer = player;
            auto SkillIter= mPlayer->PlayerSkills.find(SkillCode);
            if(SkillIter!=mPlayer->PlayerSkills.end())
                 mSkill = SkillIter->second;

        }

void PlayerSkillState::EnterState() {
    //SPDLOG_INFO("Enter SkillState");

    SkillGameObject = new GameObject();
    SkillPos = mPlayer->GetPosition();
    if(mPlayer->Flip)
        SkillPos +=Vector2(mSkill->SkillPerformPos.x,0);
    else
        SkillPos -=Vector2(mSkill->SkillPerformPos.x,0);
    SkillPos -= Vector2(0,mSkill->SkillPerformPos.y);
    SkillGameObject->SetPosition(SkillPos);

    AnimSpriteComponent* skillImg = new AnimSpriteComponent(SkillGameObject,120);
    skillImg->GetSprite()->SetFlip(mPlayer->Flip);

    // 고쳐야함 JSON 으로
    skillImg->LoopFlag  = false;
    vector<SDL_Texture*> skilltex;
    if(mSkill->ClearPlayerSpriteFlag){
        mPlayer->GetAnimSpriteComponent()->ClearSprites();
    }
    for(auto& data : mSkill->SkillImgDIR){
        SDL_Texture* Tex= Singleton<AssetLoader>::GetInstance().GetTexture(SKILL_DIR+data);
        skilltex.emplace_back(Tex);
    }

    skillImg->SetAniTextures(skilltex);
#ifdef _DEBUG
    SkillRayCastRay = new DebugRay();
    SkillRayCastRay->CreateLineRayObject(&mSkill->SkillRangeMinPos,
                                         &mSkill->SkillRangeMaxPos,Bcolor);
#endif

    skillImg->AnimationEventFrame = mSkill->SkillEventFrame;
    auto* obserbFinish = new Obserable(
        &skillImg->AnimationFinishEvent,
        skillImg->AnimationFinishEvent.Subscribe([this](int){
            GotoIdleState();
        }));

    auto* obserbTrigger = new Obserable(
            &skillImg->AnimationEvent,
            skillImg->AnimationEvent.Subscribe([this](int){
                if(!Trigged)
                    OnTrigger();
            }));
    Subscribes.emplace_back(obserbFinish);
    Subscribes.emplace_back(obserbTrigger);
}
void PlayerSkillState::OnTrigger() {
    Trigged = true;
    Vector2 minpos = Vector2(
            SkillPos.x - mSkill->SkillRangeMinPos.x,
            SkillPos.y + mSkill->SkillRangeMinPos.y);
    Vector2 maxpos = Vector2(
            SkillPos.x + mSkill->SkillRangeMaxPos.x,
            SkillPos.y - mSkill->SkillRangeMaxPos.y);
#ifdef _DEBUG
    SkillRayCastRay->CreateLineRayObject(&minpos,
                                         &maxpos,Bcolor);
#endif
    for(auto& obj : RayCastObject::BoxRayCastReturn(
                                        &minpos,
                           &maxpos,ColliderLayer::L_Enemy))
    {
        auto health = obj->GetComponent<Health>();
        if(!health->Alive)
            return;
        auto FxGameObject = new GameObject();
        FxGameObject->SetPosition(obj->GetPosition());
        AnimSpriteComponent* fxImg = new AnimSpriteComponent(FxGameObject,119);
        fxImg->GetSprite()->SetFlip(mPlayer->Flip);
        fxImg->LoopFlag  = false;
        fxImg->Killflag = true;
        vector<SDL_Texture*> fxtex;
        for(auto& data : mSkill->FxImgDIR){
            SDL_Texture* Tex= Singleton<AssetLoader>::GetInstance().GetTexture(SKILL_DIR+data);
            fxtex.emplace_back(Tex);
        }
        fxImg->SetAniTextures(fxtex);


        vector<int> damages;
        for(int i = 0 ; i<3; i++)
        {
            damages.emplace_back(10);
        }
        health->GetDamage(damages);
    }
}

void PlayerSkillState::UpdateState(float deltaTime) {
    SkillPos = mPlayer->GetPosition();
    if(mPlayer->Flip)
        SkillPos +=Vector2(mSkill->SkillPerformPos.x,0);
    else
        SkillPos -=Vector2(mSkill->SkillPerformPos.x,0);
    SkillPos -= Vector2(0,mSkill->SkillPerformPos.y);
    SkillGameObject->SetPosition(SkillPos);
}
void PlayerSkillState::GotoIdleState() {
    //auto *idleState = new PlayerIdleState(mPlayer, mMachine);

    for (auto &observe: Subscribes) {
        observe->event->UnSubscribe(observe->key);
    }
    Subscribes.clear();
    mMachine->ReFresh();
    ExitState();
    //mMachine->SwitchState(idleState);
}

void PlayerSkillState::GotoMoveState() {

}

void PlayerSkillState::ExitState() {
    SPDLOG_INFO("Exit SkillState");

    SkillGameObject->SetProcessing(false);
#ifdef _DEBUG
   delete SkillRayCastRay;
#endif
    mMachine->DeleteSubState(this);
}