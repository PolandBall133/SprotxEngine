#include "game/example_fun/snake/game.hpp"
#include "game/example_fun/snake/gen_snake_body.hpp"

using namespace boost::chrono;

namespace SnakeFun{
    const Limiter game_limiter = {-1, -1, 64, 48};
    Game::Game(GameEngine &e, GraphicsEngine &g):
        engine(e), 
        graphics(g),

        resources_path(greedy_locate_directory("resources") + "example_fun/snake/"),

        snake_segment_tex(load_texture(engine, resources_path + "segment.png")),
        fruit_tex(load_texture(engine, resources_path + "fruit.png")),

        snake(gen_snake_body(), Way::right, game_limiter),
        snake_drawer(graphics, snake, snake_segment_tex),

        fruits_manager(game_limiter, 20, seconds(5)),
        fruits_drawer(graphics, fruits_manager, fruit_tex),

        collider(fruits_manager, snake),

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
        keyboard_handler.binded_actions[{SDLK_g, KeyState::released}] = [&]{
            snake.grow();
        };
    }

    void Game::step(){
        static size_t counter = 0;
        if(++counter >= 3){
            snake.move();

            collider.check_and_react();

            counter = 0;
        }
    }

    void Game::render(){
        graphics.begin_render({170, 220, 255});
        fruits_drawer.draw();
        snake_drawer.draw();
        graphics.end_render();
    }
}