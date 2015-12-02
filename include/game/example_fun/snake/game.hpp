#pragma once

#include "game_core/game_engine.hpp"
#include "game_core/helpers/can_run.hpp"
#include "game_core/helpers/no_post.hpp"
#include "game_core/helpers/mapping_keyboard_handler.hpp"

#include "graphics_core/graphics_engine.hpp"

#include "utility/directory_utils.hpp"

#include "snake.hpp"
#include "snake_drawer.hpp"


using boost::filesystem::path;

using namespace Simplifications;

namespace SnakeFun{
    struct Game: CanRun, NoPost{
        GameEngine &engine;
        GraphicsEngine &graphics;

        const path resources_path;
        TextureHandle snake_segment;

        Snake snake;
        SnakeDrawer snake_drawer;

        MappingKeyboardHandler keyboard_handler;

        Game(GameEngine &e, GraphicsEngine &g);

        MappingKeyboardHandler &get_keyboard_handler();

        void pre();
        void step();
        void render();
    };
}