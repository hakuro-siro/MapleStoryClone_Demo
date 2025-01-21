//
// Created by binetsu on 9/10/24.
//
#include <vector>
#include "System/Physics/Rigidbody.h"
#include "System/Physics/BoxCollider.h"
#include "System/Physics/LineCollider.h"
#include "System/Utility/Singleton.h"
#include "IProcess.h"
#include "memory"

// 물리 제어용
class PhysicsProcesser : IProcess ,Singleton<PhysicsProcesser> {
public:
    PhysicsProcesser();
    ~PhysicsProcesser();

    bool Initialize() override;
    void Update(float deltaTime) override;
    void UpdatePhysics(float deltaTime);
    void Finalize() override;

    void AddCollider(BoxCollider* collider);
    void AddCollider(LineCollider* collider);
    void DeleteCollider(BoxCollider* collider);
    void DeleteCollider(LineCollider* collider);
    void CleanCollider(Collider* collider);
    /// Getter
    std::vector<LineCollider*> GetLineCollider() const { return LineColliders; }
    std::vector<BoxCollider*> GetBoxCollider() const { return BoxColliders; }
private:
    void CheckCrash();
    std::vector<BoxCollider*> BoxColliders;
    std::vector<LineCollider*> LineColliders;
    std::vector<Collider*> FixPosColliders;
}

;