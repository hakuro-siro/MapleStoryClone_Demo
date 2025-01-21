//
// Created by binetsu on 9/4/24.
//
#include "System/Component/FSM/State.h"
#include "System/Utility/Math.h"
#include "System/Utility/Event.h"
#include "PlayerState.h"

class PlayerMoveState : public PlayerState{

public:
    PlayerMoveState(class Player* player,class StateMachine* machine);
    void EnterState() override;
    void ExitState() override;
    void UpdateState(float deltaTime) override;
    void SetSprites() override;

    /// Getter - Setter
    Vector2 GetPosition(){ return position; }
    void SetX_Axis(float x){ X_AxisMovement = x; }
    void SetY_Axis(float y){ Y_AxisMovement = y; }
    float GetRightSpeed() const { return mRightSpeed; }
    float GetDownSpeed() const { return mDownSpeed; }
    void OnJumpInput() override;
    void OnKeyInput(int Keycode) override;
private:
    void UpdateMovement(float deltaTime);
    void CalculateMovement(float deltaTime);
    void CalculateMoveInput();
    void GotoJumpState();
    void GotoSkillState(int KeyCode);
    float mRightSpeed = 0;
    float mDownSpeed = 0;
    Vector2 GetForward();
    Vector2 position;
    Vector2 Movement;
    Vector2* MoveInput = nullptr;
    float MovementSpeed = 250.0f;
    float X_AxisMovement = 0;
    float Y_AxisMovement = 0;
    class Player* mPlayer;
    StateMachine* mMachine;
    std::vector<Obserable*> Subscribes;

};
