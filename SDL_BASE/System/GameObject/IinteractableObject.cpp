//
// Created by binetsu on 1/16/25.
//
#include "IinteractableObject.h"
#include "System/Process/InputReader.h"
IinteractableObject::IinteractableObject() {
    auto* InteractEvent = new Obserable(
            &Singleton<InputReader>::GetInstance().UpInputEvent,
            Singleton<InputReader>::GetInstance().UpInputEvent.Subscribe([this](int){
                Interact();}));
    Subscribes.emplace_back(InteractEvent);

}

IinteractableObject::~IinteractableObject(){
    for (auto &observe: Subscribes) {
        observe->event->UnSubscribe(observe->key);
    }
    Subscribes.clear();
}