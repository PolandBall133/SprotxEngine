#pragma once
#include "game_engine.hpp"

template<typename Game>
void loop(GameEngine &engine, Game &game){
    SDL_Event e;
    game.pre();
    while(game.is_running()){
        auto keyboard_handler = game.get_keyboard_handler();
        while(SDL_PollEvent(&e)){
            switch(e.type){
            case SDL_QUIT:
                game.set_running(false);
                break;
            }
        }
        keyboard_handler.handle(SDL_GetKeyboardState(NULL));

        game.step();
        game.render();
    }
    game.post();
}