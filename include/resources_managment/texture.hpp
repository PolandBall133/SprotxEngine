#pragma once
#include <boost/filesystem.hpp>

#include "capi_helpers/raw_capi_resource.hpp"
#include "game_core/defines.hpp"
#include "game_core/game_engine.hpp"
#include "graphics_core/graphics_engine.hpp"
#include "SDL.h"
#include "SDL_ttf.h"

RawCAPIResource<SDL_Texture> load_texture(GameEngine &engine, const boost::filesystem::path &p);

RawCAPIResource<SDL_Texture> render_text(
    GraphicsEngine &graphics, 
    TTF_Font *font, 
    const std::string &text, 
    SDL_Color color,
    size_t size
);