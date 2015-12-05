#pragma once

#include "game_core/helpers/can_run.hpp"
#include "menu/game_menu.hpp"

namespace SnakeFun{
    struct GameHolder{
        GameMenu game_menu;

        GraphicsEngine &graphics;

        GameHolder(GameEngine &engine, GraphicsEngine &graphics_engine):
            graphics(graphics_engine),
            game_menu(engine, graphics_engine){}

        auto get_keyboard_handler()
        { return game_menu.get_keyboard_handler(); }

        bool is_running() const
        { return game_menu.is_running(); }

        void set_running(bool val)
        { game_menu.set_running(val); }

        void pre(){
            YSE::System().init();
            game_menu.pre();
        }

        void step(){ 
            game_menu.step(); 
            YSE::System().update();
        }

        void render(){ 
            graphics.begin_render({170, 220, 255}); 
            game_menu.render(); 
            graphics.end_render();
        }

        void post(){
            game_menu.post();
            YSE::System().close();
        }
    };
}