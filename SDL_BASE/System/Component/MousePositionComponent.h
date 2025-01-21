#ifdef _DEBUG
#include "System/Component/Component.h"
#include "System/Utility/Event.h"
#include "System/Utility/Math.h"

class MousePositionComponent : public Component {

public:
    MousePositionComponent(class GameObject* owner, int updateOrder = 10);
    ~MousePositionComponent();
    void Update(float deltaTime) override;
    Event<int> ChangeMousePosEvent;
    int MouseX,MouseY;
    int MouseXBuf = 0,MouseYBuf = 0;
};
#endif