//
// Created by binetsu on 12/14/24.
//

#include "System/GameObject/GameObject.h"
#include "System/Utility/Singleton.h"
#include "Damage.h"
#include <vector>
using namespace std;
class DamageHandler :  IProcess ,Singleton<DamageHandler>
{
public:
    DamageHandler();

    bool Initialize() override;
    void Update(float deltaTime) override;
    void Finalize() override;

    void OnDamageHandled(class GameObject* DamagedObject, vector<int> damageList);

    vector<Damage*> Damages;
    vector<Damage*> PendingDamages;
    vector<Damage*> DeadDamages;
};

