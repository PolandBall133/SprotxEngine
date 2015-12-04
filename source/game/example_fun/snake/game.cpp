#include "game/example_fun/snake/game.hpp"
#include "game/example_fun/snake/gen_snake_body.hpp"

using namespace boost::chrono;

namespace SnakeFun{
    const Limiter game_limiter = {-1, -1, 64, 48};
    Game::Game(GameEngine &e, GraphicsEngine &g):
        engine(e), 
        graphics(g),
        text_drawer(graphics),

        resources_path(greedy_locate_directory("resources") + "example_fun/snake/"),

        fonts_system(graphics, resources_path),

        background_tex(load_texture(engine, resources_path + "background.png")),
        snake_segment_tex(load_texture(engine, resources_path + "segment.png")),
        fruit_tex(load_texture(engine, resources_path + "fruit.png")),

        snake(gen_snake_body(), Way::right, game_limiter),
        snake_drawer(graphics, snake, snake_segment_tex),

        fruits_manager(game_limiter, 20, seconds(5)),
        fruits_drawer(graphics, fruits_manager, fruit_tex),

        collider(fruits_manager, snake, eating_sound),

        input_handler(snake){}

    MappingKeyboardHandler &Game::get_keyboard_handler(){
        return input_handler.keyboard_handler;
    }

    void Game::pre(){
        YSE::System().init();

        eating_sound.create(
            (resources_path + "suck-up.wav").string().c_str(),
            &YSE::ChannelFX()
        );
        eating_sound.setSpeed(2.f);

        background_sound.create(
            (resources_path + "background.wav").string().c_str(),
            &YSE::ChannelMusic(),
            true //looped
        );
        background_sound.play();
    }

    void Game::step(){
        static size_t counter = 0;
        if(++counter >= 3){
            snake.move();

            collider.check_and_react();

            counter = 0;

            YSE::System().update();
        }
    }

    void Game::render(){
        graphics.begin_render({170, 220, 255});
        graphics.draw(background_tex.get(), 0, 0);
        text_drawer.draw(fonts_system.font("sample_font").of_size(120), "snake", 80, 80);
        fruits_drawer.draw();
        snake_drawer.draw();
        graphics.end_render();
    }

    void Game::post(){
        YSE::System().close();
    }
}