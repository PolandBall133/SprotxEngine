#include "game_core/loop.hpp"

void loop(GameEngine &engine){
    SDL_Event e;
    bool running = true;
    while(running){
        while(SDL_PollEvent(&e)){
            switch(e.type){
            case SDL_QUIT:
                running = false;
                break;
            }
        }
        SDL_RenderClear(engine.window_data.renderer());
        SDL_RenderPresent(engine.window_data.renderer());
    }
}