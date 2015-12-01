#pragma once

#include <unordered_map>
#include <functional>

struct KeyboardHandler{
    using Key = uint8_t;
    using Action = std::function<void()>;
    using KeyActionMap = std::unordered_map<Key, Action>;
    
    KeyActionMap binded_actions;
    KeyboardHandler(KeyActionMap &map): binded_actions(map){}

    template<typename Keyboard>
    void handle(Keyboard keyboard){
        for(const auto &key_action_pair : binded_actions)
            if(keyboard[key_action_pair.first])
                key_action_pair.second();
    }
};