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