#pragma once

#include "game_core/game_engine.hpp"
#include "game_core/helpers/can_run.hpp"
#include "graphics_core/graphics_engine.hpp"

#include "resources_managment/texture.hpp"
#include "resources_managment/font.hpp"

#include "utility/directory_utils.hpp"

#include "keyboard_handler.hpp"
#include "character.hpp"

using namespace std;
using namespace placeholders;
using boost::filesystem::path;

namespace Keyboardy{
    struct Game: Simplifications::CanRun{
        GameEngine &engine;
        GraphicsEngine &graphics;

        const path resources_path = greedy_locate_directory("resources") + "example_fun/keyboardy/";

        Character character;

        vector<TextureHandle> frames;
        const size_t frames_count = 2;
        size_t frame_counter = 1;
        void inc_frame_counter(){
            ++frame_counter;
            if(frame_counter > frames_count * 10)
                frame_counter = 1;
        }
        auto &get_current_frame_tex(){
            return frames.at(frame_counter / 10);
        }

        KeyboardHandler keyboard_handler = KeyboardHandler::KeyActionMap{
            {{SDLK_LEFT, KeyState::pressed}, 
             [&]{character.move = bind(&Character::move_x, ref(character), -2); }},
            {{SDLK_RIGHT, KeyState::pressed}, 
             [&]{character.move = bind(&Character::move_x, ref(character), 2); }},
            {{SDLK_UP, KeyState::pressed}, 
             [&]{character.move = bind(&Character::move_y, ref(character), -2); }},
            {{SDLK_DOWN, KeyState::pressed},  
             [&]{character.move = bind(&Character::move_y, ref(character), 2); }},
            {{SDLK_LEFT, KeyState::released}, [&]{ character.move = nullptr; }},
            {{SDLK_RIGHT, KeyState::released}, [&]{ character.move = nullptr; }},
            {{SDLK_UP, KeyState::released}, [&]{ character.move = nullptr; }},
            {{SDLK_DOWN, KeyState::released}, [&]{ character.move = nullptr; }}
        };

        Game(GameEngine &e, GraphicsEngine &g): 
            engine(e), 
            graphics(g), 
            character({100, 100}, [&]{ inc_frame_counter(); }){}

        KeyboardHandler get_keyboard_handler(){
            return keyboard_handler;
        }

        void pre(){
            for(size_t i = 0; i <= frames_count; ++i)
                frames.push_back(load_texture(engine, resources_path.string() + to_string(i) + ".png"));
        }
        void step(){
            character.update();
        }
        void render(){
            graphics.begin_render({255, 255, 255, 0});
            graphics.draw(get_current_frame_tex().get(), character.pos.x, character.pos.y);
            graphics.end_render();
        }
        void post(){
            for(auto &frame : frames)
                frame.reset();
        }
    };
};