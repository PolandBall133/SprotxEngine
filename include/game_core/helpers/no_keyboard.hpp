#pragma once

#include "mapping_keyboard_handler.hpp"

namespace Simplifications{
    struct NoKeyboard{
        MappingKeyboardHandler no_keyboard_handler{};
        auto &get_keyboard_handler()
        { return no_keyboard_handler; }
    };
}