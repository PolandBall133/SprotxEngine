#include "game/example_fun/snake/game.hpp"
#include "game/example_fun/snake/gen_snake_body.hpp"

namespace SnakeFun{
    Game::Game(GameEngine &e, GraphicsEngine &g):
        engine(e), 
        graphics(g),
        resources_path(greedy_locate_directory("resources") + "example_fun/snake/"),
        snake_segment(load_texture(engine, resources_path + "segment.png")),
        snake(gen_snake_body(), Way::right, {-1, -1, 64, 48}),
        snake_drawer(graphics, snake, snake_segment),
        keyboard_handler({}){}

    MappingKeyboardHandler &Game::get_keyboard_handler(){
        return keyboard_handler;
    }

    void Game::pre(){
        keyboard_handler.binded_actions[{SDLK_UP, KeyState::pressed}] = [&]{
            snake.set_direction(Way::up);
        };
        keyboard_handler.binded_actions[{SDLK_DOWN, KeyState::pressed}] = [&]{
            snake.set_direction(Way::down);
        };
        keyboard_handler.binded_actions[{SDLK_LEFT, KeyState::pressed}] = [&]{
            snake.set_direction(Way::left);
        };
        keyboard_handler.binded_actions[{SDLK_RIGHT, KeyState::pressed}] = [&]{
            snake.set_direction(Way::right);
        };
    }

    void Game::step(){
        static size_t counter = 0;
        if(++counter >= 3){
            snake.move();
            counter = 0;
        }
    }

    void Game::render(){
        graphics.begin_render({170, 220, 255});
        snake_drawer.draw();
        graphics.end_render();
    }
}