#pragma once
#include "game_core/game_engine.hpp"

#include "SDL_ttf.h"

class GraphicsEngine{
private:
    GameEngine &engine;
public:
    GraphicsEngine(GameEngine &e);
    SDL_Renderer *renderer();

    void begin_render(SDL_Color background_color);
    void end_render();

    void draw(SDL_Texture *texture, int x, int y);
    void draw(SDL_Rect rectangle, SDL_Color color);

    SDL_Texture *render_text(TTF_Font *font, const std::string &text, SDL_Color color);
};