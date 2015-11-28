#pragma once
#include <cinttypes>
#include <boost/utility.hpp>

#include "defines.hpp"
#include "SDL.h"
 
#include "capi_helpers/rawcapiresource.hpp"

struct GameEngine final{
    struct{
        uint32_t initialized_flags;
    } subsystems_info;
    
    struct{
        RawCAPIResource<SDL_Renderer> renderer = {NULL};
        RawCAPIResource<SDL_Window> window = {NULL};
    } window_data;
};

namespace settings{
    namespace subsystems{ 
        DEF_CONSTEXPR_STR_LITERAL(subsystems_flags_k); 
        DEF_CONSTEXPR_STR_LITERAL(init_all_v);
    }
}