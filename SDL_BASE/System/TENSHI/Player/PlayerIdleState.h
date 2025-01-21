//
// Created by binetsu on 9/7/24.
//

#include "System/Component/FSM/State.h"
#include "System/Utility/Event.h"
#include "PlayerState.h"
#include <vector>

class PlayerIdleState : public PlayerState{
public:
    PlayerIdleState(class Player* player,class StateMachine* machine);
    ~PlayerIdleState() override;
    void EnterState() override;
    void ExitState() override;
    void UpdateState(float deltaTime) override;
    void SetSprites() override;

    void OnJumpInput() override;
    void OnKeyInput(int Keycode) override;
private:
    void GotoMovementState();
    void GotoSkillState(int KeyCode);
    void GotoJumpState();
    class Player* mPlayer;

    StateMachine* mMachine;

};
