#include "game_core/game_engine.hpp"
#include "game_core/subsystems.hpp"

#include "game_core/defines.hpp"
#include "SDL.h"

int main(int argc, char **argv){
    GameEngine engine;
    init_subsystems(engine, INIT_EVERYTHING);
    return 0;
}
