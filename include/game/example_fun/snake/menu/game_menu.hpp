#pragma once

#include "game/example_fun/snake/game.hpp"

#include "game_core/helpers/no_pre.hpp"
#include "game_core/helpers/no_post.hpp"
#include "game_core/helpers/can_run.hpp"
#include "game_core/helpers/no_keyboard.hpp"

#include "graphics_core/graphics_engine.hpp"
#include "graphics_core/text_drawer.hpp"

#include "fonts_core/fonts_system.hpp"

#include "utility/directory_utils.hpp"

#include <memory>

#include "menu.hpp"

namespace SnakeFun{
    struct GameMenu:
        Simplifications::NoPre,
        Simplifications::CanRun
    {

        const path resources_path = greedy_locate_directory("resources") + "example_fun/snake/";
        std::unique_ptr<Game> game_ptr = nullptr;

        GameEngine &engine;
        GraphicsEngine &graphics;

        TextureHandle background_tex = load_texture(engine, resources_path + "background.png");

        FontsSystem fs = {graphics, resources_path};
        TextDrawer text_drawer = {graphics};

        Menu menu = {
            {"Start", [&]{ 
                game_ptr = std::make_unique<Game>(engine, graphics, fs, resources_path); 
                game_ptr->pre();
            }},
            {"Quit", [&]{ set_running(false); }}
        };

        MappingKeyboardHandler keyboard_handler = {
            {{SDLK_UP, KeyState::pressed}, [&]{ menu.selection().move_up(); }},
            {{SDLK_DOWN, KeyState::pressed}, [&]{ menu.selection().move_down(); }},
            {{SDLK_RETURN, KeyState::pressed}, [&]{ menu.selection().call(); }}
        };

        GameMenu(GameEngine &game_engine, GraphicsEngine &graphics_engine):
            engine(game_engine), 
            graphics(graphics_engine){}

        MappingKeyboardHandler &get_keyboard_handler(){
            return game_ptr?
                game_ptr->get_keyboard_handler():
                keyboard_handler;
        }

        void step(){
            if(game_ptr) game_ptr->step();
        }
        void render(){
            graphics.draw(background_tex.get(), 0, 0);
            
            if(game_ptr){
                game_ptr->render();
                return;
            }

            auto &items = menu.all_items();
            size_t y = 80, x = 220, advance = 100;
            for(size_t i = 0; i < items.size(); ++i){

                auto is_selected = items[i].text == menu.selection().text();
                auto color = is_selected? SDL_Color{0, 0, 0} : SDL_Color{100, 100, 100};

                text_drawer.draw(
                    fs.font("sample_font").of_size(80),
                    items[i].text,
                    x, y + advance*i,
                    0,
                    color);
            }
        }

        void post(){
            if(game_ptr)
                game_ptr->post();
        }
    };
}