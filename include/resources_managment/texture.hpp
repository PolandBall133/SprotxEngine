#pragma once
#include <boost/filesystem.hpp>

#include "game_core/defines.hpp"
#include "game_core/game_engine.hpp"
#include "SDL.h"

SDL_Texture *load_texture(GameEngine &engine, const boost::filesystem::path &p);