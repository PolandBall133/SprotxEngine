#include "game/example_fun/squarey_fragmented/game.hpp"

#include "game_core/subsystems.hpp"
#include "game_core/loop.hpp"

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "yse/yse.hpp"

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

    YSE::System().init();
    {{ //scope
        Squarey::Game game(engine, graphics);
        loop(engine, game);
    }}
    YSE::System().close();

    finish(engine);

    return 0;
}
