#pragma once
#include "game_engine.hpp"

template<typename Game>
void loop(GameEngine &engine, Game &game){
    SDL_Event e;
    game.pre();
    while(game.is_running()){
        while(SDL_PollEvent(&e)){
            switch(e.type){
            case SDL_QUIT:
                game.set_running(false);
                break;
            case SDL_MOUSEMOTION:
                break;
            }
        }
        game.step();
        game.render();
    }
    game.post();
}