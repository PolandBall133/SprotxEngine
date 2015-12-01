#pragma once

namespace NullObject{
    struct KeyboardHandler{
        template<typename Keyboard>
        void handle(Keyboard kb){}
    };
}