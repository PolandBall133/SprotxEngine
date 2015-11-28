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
        RawCAPIResource<SDL_Renderer> renderer = {NULL, std::bind(SDL_DestroyRenderer, std::placeholders::_1)};
        RawCAPIResource<SDL_Window> window = {NULL, std::bind(SDL_DestroyWindow, std::placeholders::_1)};
    } window_data;
};

namespace settings{
    //namespace subsystems{ 
        DEF_CONSTEXPR_STR_LITERAL_K(subsystems_flags); 
        DEF_CONSTEXPR_STR_LITERAL_V(subsystems_init_all, "INIT_EVERYTHING");
    //}
    //namespace window{
        DEF_CONSTEXPR_STR_LITERAL_K(window_width);
        DEF_CONSTEXPR_STR_LITERAL_V(window_width_example, "640");

        DEF_CONSTEXPR_STR_LITERAL_K(window_height);
        DEF_CONSTEXPR_STR_LITERAL_V(window_height_example, "480");

        DEF_CONSTEXPR_STR_LITERAL_K(window_title);
        DEF_CONSTEXPR_STR_LITERAL_V(window_title_example, "Hello World!");
    //}
}