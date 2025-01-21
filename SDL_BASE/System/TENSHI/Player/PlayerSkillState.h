//
// Created by binetsu on 9/4/24.
//
#include <string>
#include "System/Component/FSM/State.h"
#include "System/Utility/Math.h"
#include "System/TENSHI/Player/Skill/Skill.h"
#include "System/Utility/Event.h"
#include "PlayerState.h"

class PlayerSkillState : public PlayerState{

public:
    PlayerSkillState(class Player* player,class StateMachine* machine, string SkillCode);
    void EnterState() override;
    void ExitState() override;
    void UpdateState(float deltaTime) override;

    void GotoIdleState();
    void GotoMoveState();
    void OnTrigger();
    Vector2 SkillPos;
private:
    bool Trigged = false;
    class Player* mPlayer;
    class GameObject* SkillGameObject;
    Skill* mSkill;
    StateMachine* mMachine;
    std::vector<Obserable*> Subscribes;
#ifdef _DEBUG
    class DebugRay* SkillRayCastRay = nullptr;
#endif
};
