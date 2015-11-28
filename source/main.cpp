#include "game_core/game_engine.hpp"
#include "game_core/subsystems.hpp"
#include "game_core/loop.hpp"
#include "game_core/defines.hpp"

#include "resources_managment/texture.hpp"

#include "SDL.h"

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int run_tests(int argc, char **argv){
    return Catch::Session().run(argc, argv);
}

int main(int argc, char **argv){
    int tests_result = run_tests(argc, argv);
    if(tests_result != 0)
        return tests_result;

    GameEngine engine;
    init(engine, {
        {settings::subsystems_flags,
         settings::subsystems_init_all}
    });

    RawCAPIResource<SDL_Texture> sample = {
        load_texture(engine, "sample.jpg"),
        std::bind(SDL_DestroyTexture, std::placeholders::_1)
    };

    loop(engine,
        []{}, //pre
        []{}, //step
        [&]{ //render
            SDL_RenderCopy(engine.window_data.renderer(), sample(), NULL, NULL);
        }, 
        []{}  //post
    );

    finish(engine);
    return 0;
}
