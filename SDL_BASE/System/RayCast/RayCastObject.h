//
// Created by binetsu on 11/5/24.
//

#include <SDL2/SDL.h>
#include <vector>
#include "System/Physics/Collider.h"
#include "System/GameObject/GameObject.h"
using namespace std;
class RayCastObject : public Component{
public:
    RayCastObject(class GameObject* owner, int updateOrder = 100, SDL_Rect* rect = nullptr);
    ~RayCastObject();
    void Update(float deltaTime) override;
    static bool RayCast(Vector2* StartPosition, Vector2* EndPosition);
    static bool BoxRayCast(Vector2* MinPosition, Vector2* MaxPosition);
    static vector<GameObject*> BoxRayCastReturn(Vector2* MinPosition, Vector2* MaxPosition,ColliderLayer CastLayer);
    static class LineCollider* RayCastReturn(Vector2* StartPosition, Vector2* EndPosition);

};

