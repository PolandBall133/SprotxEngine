#include "resources_managment/texture.hpp"

#include "SDL_image.h"
RawCAPIResource<SDL_Texture> load_texture(GameEngine &engine, const boost::filesystem::path &p){
    auto internal = boost::filesystem::is_regular_file(p)?
        IMG_LoadTexture(engine.window_data.renderer.get(), p.string().c_str()) : nullptr;

    RawCAPIResource<SDL_Texture> result{
        internal,
        std::bind(SDL_DestroyTexture, std::placeholders::_1)
    };

    return result;
}

RawCAPIResource<SDL_Texture> render_text(
    GraphicsEngine &graphics, TTF_Font *font, const std::string &text, SDL_Color color, size_t size)
{
    RawCAPIResource<SDL_Texture> result = {
        graphics.render_text(font, text, color, size),
        std::bind(SDL_DestroyTexture, std::placeholders::_1)
    };

    return result;
}