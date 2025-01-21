//
// Created by binetsu on 12/11/24.
//

#include "MonsterData.h"

MonsterData::MonsterData(const json& data) {
    Monster_Width  = stof(data.at(Monster_Width_Key).get<std::string>());
    Monster_Height = stof(data.at(Monster_Height_Key).get<std::string>());

}
MonsterData::~MonsterData(){

}