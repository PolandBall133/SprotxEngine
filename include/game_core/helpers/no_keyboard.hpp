#pragma once

#include "null_keyboard_handler.hpp"

namespace Simplifications{
    struct NoKeyboard{
        auto get_keyboard_handler()
        { return NullObject::KeyboardHandler{}; }
    };
}