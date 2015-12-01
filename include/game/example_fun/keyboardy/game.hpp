#pragma once

#include "game_core/game_engine.hpp"
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
    struct Game{
        GameEngine &engine;
        GraphicsEngine &graphics;

        bool running = true;
        const path resources_path = greedy_locate_directory("resources").append("example_fun").append("keyboardy/");

        Character character;

        vector<RawCAPIResource<SDL_Texture>> frames;
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
            {SDLK_LEFT, [&]{
                character.pos.x -= 2;
                inc_frame_counter();
            }},
            {SDLK_RIGHT, [&]{
                character.pos.x += 2;
                inc_frame_counter();
            }},
            {SDLK_UP, [&]{
                character.pos.y -= 2;
                inc_frame_counter();
            }},
            {SDLK_DOWN, [&]{
                character.pos.y += 2;
                inc_frame_counter();
            }}
        };

        Game(GameEngine &e, GraphicsEngine &g): engine(e), graphics(g), character({100, 100}){}


        bool is_running() const{ return running; }
        void set_running(bool v){ running = v; }

        KeyboardHandler get_keyboard_handler(){
            return keyboard_handler;
        }

        void pre(){
            for(size_t i = 0; i <= frames_count; ++i)
                frames.push_back(load_texture(engine, resources_path.string() + to_string(i) + ".png"));
        }
        void step(){}
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