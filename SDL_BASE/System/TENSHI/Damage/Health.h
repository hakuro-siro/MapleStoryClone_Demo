//
// Created by binetsu on 12/14/24.
//

#include "System/Component/Component.h"
#include "System/Utility/Event.h"
#include <vector>
using namespace std;
class Health: public Component {
public:
    Health(class GameObject* owner,int Maxhp, int updateOrder = 10);
    ~Health();
    int MaxHp = 10;
    int CurrentHP;
    bool Alive = true;
    Event<int> OnDamaged;
    Event<int> OnDead;
    void GetDamage(vector<int> damageList);
};
