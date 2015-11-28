#include "game_core/subsystems.hpp"
#include "game_core/defines.hpp"

#include <boost/log/trivial.hpp>
using namespace boost;

#include "SDL.h"

void init(GameEngine &engine){
    BOOST_LOG_TRIVIAL(trace) << "Initializing game engine: calling #init_internal_subsystems";
    init_internal_subsystems(engine, INIT_EVERYTHING);
}

tribool init_internal_subsystems(GameEngine &engine, uint32_t flags){
    if(!SDL_WasInit(flags)){
        if(SDL_Init(flags) != 0){
            BOOST_LOG_TRIVIAL(error) << "SDL_Init Error: " << SDL_GetError();
            return false;
        }
        BOOST_LOG_TRIVIAL(info) << "Successfully initialized SDL subsystems (flags: " << flags << ")";
        engine.subsystems_info.initialized_flags |= flags;
        return true;
    }
    BOOST_LOG_TRIVIAL(warning) << "SDL subsystems already initialized (flags: " << flags << ")";
    return indeterminate;
}