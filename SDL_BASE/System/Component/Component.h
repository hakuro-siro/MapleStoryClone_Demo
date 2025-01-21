//
// Created by binetsu on 5/15/24.
//
/// Component 는 Process와 비슷하지만 다릅니다.
/// GameObject 에만 부착이 가능하며  Process 가 아니기 때문에 부모의 정지에 일괄적으로 정지됩니다.

#pragma once
class Component {

public:

    Component(class GameObject* owner, int updateOrder = 100);

    virtual ~Component();

    virtual void Update(float deltaTime);

    int GetUpdateOrder() const { return mUpdateOrder; }

    GameObject* GetOwner();

protected:
    class GameObject* mOwner;

    int mUpdateOrder;


};

