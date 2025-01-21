//ALL OF LOGIC Run By Process
// Initialize 의 필요성?
// 생성자와 별도의 관리되는 초기화 인자 구현용
#pragma once

#include "System/Utility/Event.h"
//Routine Interface
class IProcess
{
public:
    IProcess();
	virtual ~IProcess();

    virtual bool Initialize() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Finalize() = 0;

    void SetProcessing(bool flag) {
        if(Bind_Processer){
            SPDLOG_ERROR("This Process is Binded Processer!");
        }else{
            Processing = flag;
        }
    }
	Event<int> OnUpdate;
	Event<int> OnFinalize;

    bool Initialized = false;
    bool Processing = false;
    bool Bind_Processer = false;
};
