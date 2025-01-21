

#ifdef _DEBUG
#include <SDL2/SDL_stdinc.h>
#include "System/Component/Component.h"
#include "System/Utility/Event.h"

class FpsCheckComponent : public Component {

public:
    FpsCheckComponent(class GameObject* owner, int updateOrder = 10);
    ~FpsCheckComponent();
    void Update(float deltaTime) override;
    Event<int> FPSCountEvent;
    Uint32 CurrentTime = SDL_GetTicks();
    Uint32 LastTime = SDL_GetTicks();
    float FPS = 0.0f;
};
#endif