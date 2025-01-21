//
// Created by binetsu on 11/23/24.
//

#pragma once
#include "System/GameObject/GameObject.h"
#include "System/Component/TextComponent.h"
#include "System/Component/SpriteComponent.h"
#include <unordered_map>

#ifdef _DEBUG
#include "System/Utility/DebugRay.h"
#endif

class Canvas : public GameObject {
public:
    Canvas();
    ~Canvas();
    void AddTextComp(std::string componentName, TextComponent* TComoponent){
        mTextComponents.emplace(componentName.c_str(),TComoponent);
    }
    void AddSpriteComp(std::string componentName, SpriteComponent* SComoponent){
        mSpriteComponents.emplace(componentName.c_str(),SComoponent);
    }
    TextComponent* GetTextComp(std::string componentName)
    {
        if(mTextComponents[componentName]!= nullptr)
            return mTextComponents[componentName];
        else
            SPDLOG_ERROR("Can Not Found {} in Canvas",componentName);
        return nullptr;
    }
    SpriteComponent* GetSpriteComp(std::string componentName)
    {
        if(mSpriteComponents[componentName]!= nullptr)
            return mSpriteComponents[componentName];
        else
            SPDLOG_ERROR("Can Not Found {} in Canvas",componentName);
        return nullptr;
    }

#ifdef _DEBUG
    class DebugRay* CanvasdebugRay;
#endif

protected:
    unordered_map<std::string,TextComponent*> mTextComponents;
    unordered_map<std::string,SpriteComponent*> mSpriteComponents;
};
