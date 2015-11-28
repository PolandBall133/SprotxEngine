#include "game_core/subsystems.hpp"
#include "game_core/defines.hpp"

#include <boost/log/trivial.hpp>
using namespace boost;
using namespace std;

#include "SDL.h"
#include "SDL_ttf.h"

void init(GameEngine &engine, const SettingsMap &settings){
    init_internal_subsystems(engine, settings);
    init_window(engine, settings);
    init_renderer(engine);
    TTF_Init();
}

void finish(GameEngine &engine){
    SDL_Quit();
    TTF_Quit();
}

tribool init_internal_subsystems(GameEngine &engine, const SettingsMap &settings){
    auto flags = settings.count(settings::subsystems_flags)?
        settings.at(settings::subsystems_flags) == settings::subsystems_init_all?
            INIT_EVERYTHING
            : stoul(settings.at(settings::subsystems_flags))
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

void init_window(GameEngine &engine, const SettingsMap &settings){
    size_t width = stoul(settings.count(settings::window_width)?
        settings.at(settings::window_width)
        : settings::window_width_example);

    size_t height = stoul(settings.count(settings::window_height)?
        settings.at(settings::window_height)
        : settings::window_height_example);

    const char *title = settings.count(settings::window_title)?
        settings.at(settings::window_title).c_str()
        : settings::window_title_example;

    BOOST_LOG_TRIVIAL(trace) << "Initializing game engine: calling #init_window"
        << "(width: " << width << ", height: " << height << ")";
    init_window(engine, width, height, title);
}

void init_window(GameEngine &engine, size_t width, size_t height, const char *title){
    engine.window_data.window.reset(
        SDL_CreateWindow(
            title, 
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            width, height, 
            SDL_WINDOW_SHOWN
        )
    );
}

void init_renderer(GameEngine &engine){
    BOOST_LOG_TRIVIAL(trace) << "Initializing game engine: calling #init_renderer";
    engine.window_data.renderer.reset(
        SDL_CreateRenderer(engine.window_data.window(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
    );
}