//
// Created by binetsu on 10/19/24.
//
#include "IProcess.h"
#include "System/Utility/Singleton.h"
#include "Processer.h"

IProcess::IProcess() {
    Singleton<Processer>::GetInstance().RegisterProcesser(this);
}

bool IProcess::Initialize() {
    Initialized = true;
    Processing = true;
    return true;
}
void IProcess::Finalize() {

}

IProcess::~IProcess(){
    Singleton<Processer>::GetInstance().UnRegisterProcesser(this);
}
