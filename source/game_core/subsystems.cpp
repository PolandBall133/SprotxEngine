#include "game_core/subsystems.hpp"
#include "game_core/defines.hpp"

#include <boost/log/trivial.hpp>
using namespace boost;
using namespace std;

#include "SDL.h"

void init(GameEngine &engine, const SettingsMap &settings){
    init_internal_subsystems(engine, settings);
}

tribool init_internal_subsystems(GameEngine &engine, const SettingsMap &settings){
    using namespace settings::subsystems;
    auto flags = settings.count(subsystems_flags_k)?
        settings.at(subsystems_flags_k) == init_all_v?
            INIT_EVERYTHING
            : stoul(settings.at(subsystems_flags_k))
        : 0;
    BOOST_LOG_TRIVIAL(trace) << "Initializing game engine: calling #init_internal_subsystems (flags: " << flags << ")";
    return init_internal_subsystems(engine, flags);
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

void init_window_data(GameEngine &engine, const SettingsMap &settings){

}