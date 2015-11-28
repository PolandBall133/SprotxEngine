#include "resources_managment/texture.hpp"

#include "SDL_image.h"
SDL_Texture *load_texture(GameEngine &engine, const boost::filesystem::path &p){
    return boost::filesystem::is_regular_file(p) ?
        IMG_LoadTexture(engine.window_data.renderer(), p.string().c_str()) : nullptr;
}