#pragma once

namespace NullObject{
    struct KeyboardHandler{
        template<typename IgnoreKey, typename IgnoreState>
        void handle(IgnoreKey, IgnoreState){}
    };
}