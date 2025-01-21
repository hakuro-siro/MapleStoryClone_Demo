//
// Created by binetsu on 9/4/24.
//
#include "System/Component/FSM/State.h"
#include "System/Utility/Math.h"
#include "PlayerState.h"
class PlayerJumpState : public PlayerState{

public:
    PlayerJumpState(class Player* player,class StateMachine* machine);
    void EnterState() override;
    void ExitState() override;
    void UpdateState(float deltaTime) override;
    void SetSprites() override;

    int JumpPower = -9.0;
    Vector2 JumpVelocity = Vector2(0,JumpPower);
    /// Getter - Setter
    Vector2 GetPosition(){ return position; }
    bool IsJumping = false;

    void OnJumpInput() override;
    void OnKeyInput(int Keycode) override;
private:
    void UpdateMovement(float deltaTime);
    void CalculateMovement(float deltaTime);
    void CalculateMoveInput();
    void GotoSkillState(int KeyCode);
    Vector2 position;
    Vector2 Movement;
    Vector2* MoveInput = nullptr;
    float MovementSpeed = 200.0f;
    float X_AxisMovement = 0;
    float Y_AxisMovement = 0;
    class Player* mPlayer;
    StateMachine* mMachine;

};
