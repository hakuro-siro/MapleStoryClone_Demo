//
// Created by binetsu on 12/7/24.
//

#include "LineColliderData.h"

LineColliderData::LineColliderData(const json &data) {
    PosA  = Vector2(stoi(data.at(PosA_X_Key).get<std::string>()),
                    stoi(data.at(PosA_Y_Key).get<std::string>()));
    PosB  = Vector2(stoi(data.at(PosB_X_Key).get<std::string>()),
                    stoi(data.at(PosB_Y_Key).get<std::string>()));
}
LineColliderData::~LineColliderData() {}