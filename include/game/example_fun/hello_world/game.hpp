#pragma once

#include "game_core/game_engine.hpp"
#include "game_core/helpers/no_keyboard.hpp"
#include "game_core/helpers/can_run.hpp"

#include "graphics_core/graphics_engine.hpp"

#include "resources_managment/texture.hpp"
#include "resources_managment/font.hpp"

#include "rectangles_manager.hpp"

#include "utility/directory_utils.hpp"

#include <utility>
using namespace std;
using namespace placeholders;
using boost::filesystem::path;
using namespace Simplifications;
namespace HelloWorld{
    struct Game: CanRun, NoKeyboard{
        GameEngine &engine;
        GraphicsEngine &graphics;
        RectanglesManager rm;

        const path resources_path = greedy_locate_directory("resources")+"/example_fun/hello_world";
        Game(GameEngine &e, GraphicsEngine &g): engine(e), graphics(g){}

        TextureHandle sample_image = load_texture(engine, resources_path.string() + "/sample.jpg");

        FontHandle sample_font = load_font(engine, resources_path.string() + "/sample.ttf", 60);

        TextureHandle sample_rendered_text = render_text(
            graphics, sample_font.get(), "Hello World!", {255, 255, 255}, 60);

        void pre(){
            rm.gen();
        }
        void step(){}
        void render(){
            graphics.begin_render({0, 0, 0, 0});

            graphics.draw(sample_image.get(), 10, 10);
            graphics.draw(sample_rendered_text.get(), 200, 400);
            for(auto &colored_rect : rm.rects)
                graphics.draw(colored_rect.rect, colored_rect.color);
            graphics.end_render();
        }
        void post(){
            sample_image.reset(nullptr);
            sample_font.reset(nullptr);
            sample_rendered_text.reset(nullptr);
        }
    };
}