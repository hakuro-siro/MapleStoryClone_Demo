//
// Created by binetsu on 9/4/24.
//
#include "System/Component/FSM/State.h"
#include "System/Utility/Math.h"
#include "PlayerState.h"
class PlayerDoubleJumpState : public PlayerState{

public:
    PlayerDoubleJumpState(class Player* player,class StateMachine* machine);
    void EnterState() override;
    void ExitState() override;
    void UpdateState(float deltaTime) override;
    void SetSprites() override;

    int JumpPower = -5.0;
    Vector2 JumpVelocity = Vector2(0,JumpPower);
    /// Getter - Setter
    Vector2 GetPosition(){ return position; }
    bool IsJumping = false;
    void OnJumpInput() override {};
    void OnKeyInput(int Keycode) override;
    void OnJumpFxEnd();
private:
    void UpdateMovement(float deltaTime);
    void CalculateMovement(float deltaTime);
    void GotoSkillState(int KeyCode);
    float MovementSpeed = 450.0f;
    float X_AxisMovement = 1;
    float Y_AxisMovement = 0;

    class GameObject* SkillGameObject;
    Vector2 position;
    Vector2 Movement;
    Vector2* MoveInput = nullptr;
    class Player* mPlayer;
    StateMachine* mMachine;
    class Skill* mSkill;
};
