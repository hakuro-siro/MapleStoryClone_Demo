//
// Created by binetsu on 11/26/24.
//
#include "System/UI/View/Canvas.h"
class TitleCanvas : public Canvas{
public:
    TitleCanvas();
    void gotoIngame();
    bool Initialize() override;
    ~TitleCanvas();
    const std::string TITLE_TEXT ="TITLE_TEXT";
    const std::string TITL2_TEXT ="TITLE2_TEXT";
    const std::string START_TEXT ="START_TEXT";
private:

    std::vector<Obserable*> Subscribes;
};
