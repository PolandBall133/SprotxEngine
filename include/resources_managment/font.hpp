#pragma once
#include <boost/filesystem.hpp>

#include "capi_helpers/raw_capi_resource.hpp"
#include "game_core/defines.hpp"
#include "game_core/game_engine.hpp"
#include "SDL_ttf.h"

RawCAPIResource<TTF_Font> load_font(const boost::filesystem::path &p, size_t size);

using FontHandle = RawCAPIResource<TTF_Font>;