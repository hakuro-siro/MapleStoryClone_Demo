//
// Created by binetsu on 11/26/24.
//
#include "System/UI/View/Canvas.h"
#ifdef _DEBUG
class DebugCanvas : public Canvas{
public:
    DebugCanvas();
    bool Initialize() override;
    ~DebugCanvas();
};

const std::string FPS_TEXT ="FPS_TEXT";
const std::string MP_TEXT ="MP_TEXT";
#endif