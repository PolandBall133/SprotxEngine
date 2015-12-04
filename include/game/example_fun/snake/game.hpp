#pragma once

#include "game_core/game_engine.hpp"
#include "game_core/helpers/can_run.hpp"
#include "game_core/helpers/mapping_keyboard_handler.hpp"

#include "graphics_core/graphics_engine.hpp"
#include "graphics_core/text_drawer.hpp"

#include "yse/yse.hpp"
#include "fonts_core/fonts_system.hpp"

#include "utility/directory_utils.hpp"

#include "snake.hpp"
#include "snake_drawer.hpp"

#include "fruits_manager.hpp"
#include "fruits_drawer.hpp"

#include "collider.hpp"

using boost::filesystem::path;

using namespace Simplifications;

namespace SnakeFun{
    struct Game: CanRun{
        GameEngine &engine;
        GraphicsEngine &graphics;
        TextDrawer text_drawer;

        const path resources_path;

        FontsSystem fonts_system;


        TextureHandle background_tex;
        TextureHandle snake_segment_tex;
        TextureHandle fruit_tex;

        Snake snake;
        SnakeDrawer snake_drawer;

        FruitsManager fruits_manager;
        FruitsDrawer fruits_drawer;

        Collider collider;

        YSE::sound eating_sound;
        YSE::sound background_sound;

        SnakeInputHandler input_handler;

        Game(GameEngine &e, GraphicsEngine &g);

        MappingKeyboardHandler &get_keyboard_handler();

        void pre();
        void step();
        void render();
        void post();
    };
}