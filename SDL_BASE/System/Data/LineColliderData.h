//
// Created by binetsu on 12/7/24.
//
#include "json.hpp"
#include "System/Utility/Math.h"
#include <string>

using namespace std;
using json = nlohmann::json;

class LineColliderData {

public:
    LineColliderData(const json& data);
    ~LineColliderData();
    Vector2 PosA;
    Vector2 PosB;
};
const string PosA_X_Key = "PosA_X";
const string PosA_Y_Key = "PosA_Y";
const string PosB_X_Key = "PosB_X";
const string PosB_Y_Key = "PosB_Y";
const string ColliderMap_Key = "ColliderMap";
