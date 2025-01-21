//
// Created by binetsu on 11/12/24.
//

#include "PlayerState.h"
#include "System/Process/InputReader.h"

PlayerState::PlayerState() {

}
void PlayerState::RefreshState() {
    SetSprites();
}
void PlayerState::EnterState() {
    auto* JumpEvent = new Obserable(
            &Singleton<InputReader>::GetInstance().JumpInputEvent,
            Singleton<InputReader>::GetInstance().JumpInputEvent.Subscribe([this](int){
                OnJumpInput();}));
    auto* SkillEvent = new Obserable(
            &Singleton<InputReader>::GetInstance().SkillInputEvent,
            Singleton<InputReader>::GetInstance().SkillInputEvent.Subscribe([this](int arg){
                OnKeyInput(arg);}));

    Subscribes.emplace_back(JumpEvent);
    Subscribes.emplace_back(SkillEvent);
}

void PlayerState::ExitState() {
    for (auto &observe: Subscribes) {
        observe->event->UnSubscribe(observe->key);
    }
    Subscribes.clear();
}

void PlayerState::OnKeyInput(int Keycode) {}
void PlayerState::OnJumpInput() {}