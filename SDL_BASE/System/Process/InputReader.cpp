//
// Created by binetsu on 9/7/24.
//

#include <SDL2/SDL_events.h>
#include "InputReader.h"
#include "Processer.h"
#include "Renderer.h"

InputReader::InputReader() : MovementInputVector(Vector2::Zero)
{
}

bool InputReader::Initialize()
{

    IProcess::Initialize();

    Bind_Processer = true;
    return true;
}

void InputReader::Update(float deltaTime)
{
    ProcessInput(deltaTime);
}

void InputReader::Finalize()
{
}

/*
 * Input
 */
void InputReader::ProcessInput(float deltaTime)
{
    if (Singleton<Processer>::GetInstance().SceneMoving)
    {
        MovementInputVector.x = 0;
        MovementInputVector.y = 0;
        return;
    }
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Singleton<Processer>::GetInstance().SetIsRunning(false);
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_LALT && !JumpPerformed)
            {
                JumpInputEvent.OnNext(0);
                JumpPerformed = true;
            }
            if (event.key.keysym.sym == SDLK_UP && !JumpPerformed)
            {
                UpInputEvent.OnNext(0);
            }
            if (event.key.keysym.sym == SDLK_F1 && !Pressed)
            {
                // Singleton<Processer>::GetInstance().ClearGameObject();
            }
            if (event.key.keysym.sym == SDLK_F2 && !Pressed)
            {
                // Singleton<Processer>::GetInstance().ReloadScene();
            }
            if (event.key.keysym.sym == SDLK_d && !Pressed)
            {
                SkillInputEvent.OnNext(1);
            }
            if (event.key.keysym.sym == SDLK_SPACE && !Pressed)
            {
                GameStartEvent.OnNext(1);
            }
            Pressed = true;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_LALT && JumpPerformed)
            {
                JumpPerformed = false;
            }
            Pressed = false;
        }
        const Uint8 *state = SDL_GetKeyboardState(NULL);

        // right/left
        if (state[SDL_SCANCODE_RIGHT])
        {
            MovementInputVector.x = 1;
        }
        else if (state[SDL_SCANCODE_LEFT])
        {
            MovementInputVector.x = -1;
        }
        else
        {
            MovementInputVector.x = 0;
        }
        // up/down
        if (state[SDL_SCANCODE_DOWN])
        {
            MovementInputVector.y = -1;
        }
        else if (state[SDL_SCANCODE_UP])
        {
            MovementInputVector.y = 1;
        }
        else
        {
            MovementInputVector.y = 0;
        }

        if (state[SDL_SCANCODE_ESCAPE])
        {
            Singleton<Renderer>::GetInstance().ClearSprites();
        }
    }
}
