#include "graphics_core/graphics_engine.hpp"
#include "boost/log/trivial.hpp"

GraphicsEngine::GraphicsEngine(GameEngine &e): engine(e){}

SDL_Renderer *GraphicsEngine::renderer(){
    return engine.window_data.renderer();
}

void GraphicsEngine::draw(SDL_Texture *texture, size_t x, size_t y){
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect dest = {x, y, w, h};
    if(SDL_RenderCopy(renderer(), texture, NULL, &dest)){
        BOOST_LOG_TRIVIAL(error) << SDL_GetError();
    }
}

SDL_Texture *GraphicsEngine::render_text(TTF_Font *font, const std::string &text, SDL_Color color, size_t font_size){
    SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), color);
    if(surf == nullptr){
        BOOST_LOG_TRIVIAL(error) << SDL_GetError();
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer(), surf);
    if(texture == nullptr)
        BOOST_LOG_TRIVIAL(error) << SDL_GetError();
    SDL_FreeSurface(surf);
    return texture;
}