//
// Created by binetsu on 9/7/24.
//
#include "System/Utility/Event.h"
#include "System/Utility/Math.h"
#include "System/Utility/Singleton.h"
#include "IProcess.h"

class InputReader : IProcess, Singleton<InputReader>{
public:
    InputReader();

    bool Initialize() override;
    void Update(float deltaTime) override;
    void Finalize() override;

    Vector2 MovementInputVector;
    Event<int> UpInputEvent;
    Event<int> JumpInputEvent;

    Event<int> GameStartEvent;
    Event<int> SkillInputEvent;
private:
    void ProcessInput(float deltaTime);
    bool JumpPerformed = false;
    bool Pressed = false;
};
