#pragma once

#include <map>
#include <functional>

#include "game_core/defines.hpp"
#include "SDL.h"

enum struct KeyState{ pressed, released };

struct MappingKeyboardHandler{
    using Key = std::pair<SDL_Keycode, KeyState>;
    using Action = std::function<void()>;
    using KeyActionMap = std::map<Key, Action>;

    KeyActionMap binded_actions;
    MappingKeyboardHandler(KeyActionMap &map): binded_actions(map){}
    MappingKeyboardHandler(const KeyActionMap &map): binded_actions(map){}
    MappingKeyboardHandler(): binded_actions(){}


    void handle(SDL_Keysym key, Uint8 state){
        Key mapped_key = {key.sym, state == SDL_PRESSED ? KeyState::pressed : KeyState::released};
        if(binded_actions.count(mapped_key))
            binded_actions[mapped_key]();
    }
};