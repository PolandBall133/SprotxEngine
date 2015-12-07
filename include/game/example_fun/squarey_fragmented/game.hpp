#pragma once
#include <game_core/helpers/no_keyboard.hpp>
#include <game_core/helpers/can_run.hpp>
#include <game_core/game_engine.hpp>
#include <graphics_core/graphics_engine.hpp>

#include "core/scene.hpp"
#include "connections/summary.hpp"
namespace Squarey{
    struct Game:
        Simplifications::NoKeyboard,
        Simplifications::CanRun
    {

        GraphicsEngine &graphics;
        Scene scene;

        Game(GameEngine &e, GraphicsEngine &ge):
            graphics(ge),
            scene(e, ge){}

        void pre(){
            attach_connections_to_scene(scene);
        }
        void step(){
            scene.scripts.update_all();
        }
        void render(){
            graphics.begin_render({200, 255, 200});
            scene.scripts.render_all();
            graphics.end_render();
        }
        void post(){
            scene.scripts.unregister_all();
        }
    };
}