#pragma once

#include <map>
#include <functional>
#include <initializer_list>

#include "game_core/defines.hpp"
#include "SDL.h"

enum struct KeyState{ pressed, released };

struct MappingKeyboardHandler{
    using Key = std::pair<SDL_Keycode, KeyState>;
    using Action = std::function<void()>;
    using KeyActionMap = std::map<Key, Action>;

    KeyActionMap binded_actions;
    MappingKeyboardHandler(const KeyActionMap &map): binded_actions(map){}
    MappingKeyboardHandler(const std::initializer_list<KeyActionMap::value_type> &il): binded_actions(il){}


    void handle(SDL_Keysym key, Uint8 state){
        Key mapped_key = {key.sym, state == SDL_PRESSED ? KeyState::pressed : KeyState::released};
        if(binded_actions.count(mapped_key))
            binded_actions[mapped_key]();
    }
};