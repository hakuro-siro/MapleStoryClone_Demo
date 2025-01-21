//
// Created by binetsu on 11/26/24.
//

#include "System/UI/View/Canvas.h"
#include "System/Process/IProcess.h"

class Presentor : public GameObject {
public:
    Presentor();
    ~Presentor();
    virtual void SetCanvas(Canvas& canvas) { mCanvas = &canvas;}
    virtual void BindModelView();
protected:
    Canvas* mCanvas;
    std::vector<Obserable*> Subscribes;
};
