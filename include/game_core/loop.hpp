#pragma once
#include "game_engine.hpp"

template<typename Fpre, typename Fstep, typename Frender, typename Fpost>
void loop(GameEngine &engine, Fpre &&pre_func, Fstep &&step_func, Frender &&render_func, Fpost &&post_func){
    SDL_Event e;
    bool running = true;
    pre_func();
    while(running){
        while(SDL_PollEvent(&e)){
            switch(e.type){
            case SDL_QUIT:
                running = false;
                break;
            }
        }
        step_func();
        SDL_RenderClear(engine.window_data.renderer());
        render_func();
        SDL_RenderPresent(engine.window_data.renderer());
    }
    post_func();
}