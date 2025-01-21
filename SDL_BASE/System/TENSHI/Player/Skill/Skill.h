//
// Created by binetsu on 9/7/24.
//

#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "json.hpp"
#include "System/Utility/Math.h"

using namespace std;
using json = nlohmann::json;

enum SkillType{
    Active,
    Buff
};

enum SkillCode{
    A_00001,
    A_00002,
    J_00001
};
const std::unordered_map<string ,SkillCode> SkillCodeMap{
        {"A_00001",SkillCode::A_00001},
        {"A_00002",SkillCode::A_00002},
        {"J_00002",SkillCode::J_00001}
};

const std::unordered_map<string,SkillType> SkillTypeMap{
        {"Active",SkillType::Active},
        {"Buff",SkillType::Buff},
};

const std::unordered_map<int,string> SkillInputMap{
        {1,"D"},
        {2,"F4"},
};


class Skill{
    public:
        Skill(const json& data);
        ~Skill();
        SkillCode mSkillCode;
        SkillType mSkillType;
        string mSkillKey;
        Vector2 SkillPerformPos = Vector2::Zero;
        Vector2 SkillRangeMinPos = Vector2::Zero;
        Vector2 SkillRangeMaxPos = Vector2::Zero;
        int SkillEventFrame = 0;
        bool ClearPlayerSpriteFlag = false;
        string mSkillName;
        vector<string> SkillImgDIR;
        vector<string> FxImgDIR;
};

const string SkillCodeKey = "SkillCode";
const string SkillNameKey = "SkillName";
const string SkillKeyKey = "SkillKey";
const string SkillTypeKey = "SkillType";
const string ClearPlayerSpriteFlag_Key = "ClearPlayer";
const string SkillPerformPosX_Key = "PosX";
const string SkillPerformPosY_Key = "PosY";
const string SkillRangeMinPosX_Key = "MinPosX";
const string SkillRangeMinPosY_Key = "MinPosY";
const string SkillRangeMaxPosX_Key = "MaxPosX";
const string SkillRangeMaxPosY_Key = "MaxPosY";
const string SkillEventFrameKey = "EventFrame";

const string PlayerSkillsKey = "PlayerSkills";
const string SkillImgDIRKey = "SkillImgDIR";
const string FxImgDIRKey = "FxImgDIR";
const string SkillDataDIRKey = "SkillDataDIR";
//FxImgDIR
