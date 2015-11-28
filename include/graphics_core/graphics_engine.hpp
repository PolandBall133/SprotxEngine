#pragma once
#include "game_core/game_engine.hpp"

class GraphicsEngine{
private:
    GameEngine &engine;
public:
    GraphicsEngine(GameEngine &e);
    SDL_Renderer *renderer();

    void draw(SDL_Texture *texture, size_t x, size_t y);
};