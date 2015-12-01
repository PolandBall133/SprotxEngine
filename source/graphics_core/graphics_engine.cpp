#include "graphics_core/graphics_engine.hpp"
#include "boost/log/trivial.hpp"

GraphicsEngine::GraphicsEngine(GameEngine &e): engine(e){}

SDL_Renderer *GraphicsEngine::renderer(){
    return engine.window_data.renderer.get();
}

void GraphicsEngine::begin_render(SDL_Color background_color){
    SDL_SetRenderDrawColor(
        renderer(), 
        background_color.r, 
        background_color.g, 
        background_color.b, 
        background_color.a
    );
    SDL_RenderClear(renderer());
}

void GraphicsEngine::end_render(){
    SDL_RenderPresent(renderer());
}

void GraphicsEngine::draw(SDL_Texture *texture, int x, int y){
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect dest = {x, y, w, h};
    if(SDL_RenderCopy(renderer(), texture, NULL, &dest)){
        BOOST_LOG_TRIVIAL(error) << SDL_GetError();
    }
}

void GraphicsEngine::draw(SDL_Rect rectangle, SDL_Color c){
    SDL_SetRenderDrawColor(renderer(), c.r, c.g, c.b, c.a);
    SDL_RenderDrawRect(renderer(), &rectangle);
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