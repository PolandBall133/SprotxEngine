#include "game/example_fun/snake/game_holder.hpp"

#include "game_core/subsystems.hpp"
#include "game_core/loop.hpp"

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
    GraphicsEngine graphics(engine);
    init(engine, {
        {settings::subsystems_flags,
            settings::subsystems_init_all}
    });

    {{ //scope
        SnakeFun::GameHolder game(engine, graphics);
        loop(engine, game);
    }}

    finish(engine);

    return 0;
}
