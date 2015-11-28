#include "game_core/game_engine.hpp"
#include "game_core/subsystems.hpp"
#include "game_core/loop.hpp"
#include "game_core/defines.hpp"

#include "graphics_core/graphics_engine.hpp"

#include "resources_managment/texture.hpp"

#include "SDL.h"

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int run_tests(int argc, char **argv){
    return Catch::Session().run(argc, argv);
}

using namespace std;
using namespace placeholders;

struct Game{
    GameEngine &engine;
    GraphicsEngine &graphics;
    Game(GameEngine &e, GraphicsEngine &g): engine(e), graphics(g){}

    RawCAPIResource<SDL_Texture> sample_image = {
        load_texture(engine, "sample.jpg"),
        bind(SDL_DestroyTexture, _1)
    };

    RawCAPIResource<TTF_Font> sample_font = {
        TTF_OpenFont("sample.ttf", 60),
        bind(TTF_CloseFont, _1)
    };

    RawCAPIResource<SDL_Texture> sample_rendered_text = {
        graphics.render_text(sample_font(), "Hello World!", {255, 255, 255}, 60),
        bind(SDL_DestroyTexture, _1)
    };

    void pre(){}
    void step(){}
    void render(){
        graphics.draw(sample_image(), 10, 10);
        graphics.draw(sample_rendered_text(), 200, 400);
    }
    void post(){
        sample_image.reset(nullptr);
        sample_font.reset(nullptr);
        sample_rendered_text.reset(nullptr);
    }
};

int main(int argc, char **argv){
    int tests_result = run_tests(argc, argv);
    if(tests_result != 0)
        return tests_result;

    GameEngine engine;
    GraphicsEngine graphics(engine);
    init(engine, {
        {settings::subsystems_flags,
         settings::subsystems_init_all}
    });
    
    Game game(engine, graphics);
    loop(engine,
        bind(&Game::pre, &game),
        bind(&Game::step, &game),
        bind(&Game::render, &game),
        bind(&Game::post, &game)
    );

    finish(engine);
    return 0;
}
