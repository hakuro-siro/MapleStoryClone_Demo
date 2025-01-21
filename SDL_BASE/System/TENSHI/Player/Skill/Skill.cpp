//
// Created by binetsu on 11/9/24.
//

#include "Skill.h"

Skill::Skill(const json& data){
    auto SkillCodeIter= SkillCodeMap.find(data.at(SkillCodeKey).get<std::string>());
    if(SkillCodeIter!=SkillCodeMap.end())
        mSkillCode = SkillCodeIter->second;

    SkillRangeMinPos.x = stof(data.at(SkillRangeMinPosX_Key).get<std::string>());
    SkillRangeMinPos.y = stof(data.at(SkillRangeMinPosY_Key).get<std::string>());
    SkillRangeMaxPos.x = stof(data.at(SkillRangeMaxPosX_Key).get<std::string>());
    SkillRangeMaxPos.y = stof(data.at(SkillRangeMaxPosY_Key).get<std::string>());
    SkillPerformPos.x = stof(data.at(SkillPerformPosX_Key).get<std::string>());
    SkillPerformPos.y = stof(data.at(SkillPerformPosY_Key).get<std::string>());


    ClearPlayerSpriteFlag = stoi(data.at(ClearPlayerSpriteFlag_Key).get<std::string>());
    mSkillName = data.at(SkillNameKey).get<std::string>();
    mSkillKey = data.at(SkillKeyKey).get<std::string>();

    auto SkillTypeIter = SkillTypeMap.find(data.at(SkillTypeKey).get<std::string>());
    if(SkillTypeIter!=SkillTypeMap.end())
        mSkillType = SkillTypeIter->second;

    SkillEventFrame = stoi(data.at(SkillEventFrameKey).get<std::string>());
}

Skill::~Skill() {

}