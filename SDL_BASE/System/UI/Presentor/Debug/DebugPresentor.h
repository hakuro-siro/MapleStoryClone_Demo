//
// Created by binetsu on 11/26/24.
//
#ifdef _DEBUG
#include "System/UI/Presentor/Presentor.h"

class DebugPresentor : public Presentor {
public:
    DebugPresentor();
    ~DebugPresentor();
    void SetCanvas(Canvas &canvas) override;
    void SetEventHandler(class FpsCheckComponent& Fpshandler,
                        class MousePositionComponent& Mousehandler);
    void BindModelView() override;
    class FpsCheckComponent* FpsCheckEventHandler;
    class MousePositionComponent* MousePositionEventHandler;
    class DebugCanvas* mDebugCanvas;
};

#endif
