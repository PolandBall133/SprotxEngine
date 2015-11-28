#pragma once
#include "game_core/game_engine.hpp"

#include "SDL_ttf.h"

class GraphicsEngine{
private:
    GameEngine &engine;
public:
    GraphicsEngine(GameEngine &e);
    SDL_Renderer *renderer();

    void draw(SDL_Texture *texture, size_t x, size_t y);

    SDL_Texture *render_text(TTF_Font *font, const std::string &text, SDL_Color color, size_t font_size);
};