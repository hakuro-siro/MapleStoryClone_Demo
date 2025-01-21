//
// Created by binetsu on 9/7/24.
//

#include <functional>
#include "spdlog/spdlog.h"

#pragma once


template<typename ... Args>
class Event {
public:
    using Type = std::function<void(Args...)>;

    int Subscribe(Type func) {
        int key = CurrentKey;
        functions[key] = func;
        CurrentKey++;
        //SPDLOG_INFO("Subscribed Key {}",key);
        return key;
    }

    void UnSubscribe(int key) {

        //SPDLOG_INFO("UnSubscribe Key {}",key);
        UnsubscribeKeys.emplace_back(key);
    }

    void OnNext(int args) {
        for (auto key: UnsubscribeKeys) {
            if(functions.find(key)==functions.end()){
                SPDLOG_INFO("There is Nothing to Erase Key : {}",key);
                continue;
            }
            if(functions.erase(key)!=0) {
                //SPDLOG_INFO("UnSubscribed {}",key);
            }
            else
                SPDLOG_ERROR("UnSubscribed - FAIL!! {}",key);
        }
        UnsubscribeKeys.clear();

        for (const auto &[id, func]: functions) {
            func(std::forward<int>(args));
        }
    }

private:
    int CurrentKey = 0;
    std::unordered_map<int, Type> functions;
    std::vector<int> UnsubscribeKeys;
};

class Obserable {
public:
    Event<int>* event;
    int key;
public:
    Obserable(Event<int>* Event, int Key) {
        event = Event;
        key = Key;
    }
};
