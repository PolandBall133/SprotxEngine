#pragma once

#include "game_core/game_engine.hpp"
#include "graphics_core/graphics_engine.hpp"
#include "resources_managment/texture.hpp"
#include "rectangles_manager.hpp"

#include "utility/directory_utils.hpp"

#include <utility>
using namespace std;
using namespace placeholders;
using boost::filesystem::path;

struct Game{
    GameEngine &engine;
    GraphicsEngine &graphics;
    RectanglesManager rm;

    const path resources_path = greedy_locate_directory("resources").append("example_fun").append("hello_world");
    Game(GameEngine &e, GraphicsEngine &g): engine(e), graphics(g){}

    bool running = true;
    bool is_running() const{ return running; }
    void set_running(bool v){ running = v; }

    RawCAPIResource<SDL_Texture> sample_image = {
        load_texture(engine, resources_path.string()+"/sample.jpg"),
        bind(SDL_DestroyTexture, _1)
    };

    RawCAPIResource<TTF_Font> sample_font = {
        TTF_OpenFont((resources_path.string()+"/sample.ttf").c_str(), 60),
        bind(TTF_CloseFont, _1)
    };

    RawCAPIResource<SDL_Texture> sample_rendered_text = {
        graphics.render_text(sample_font(), "Hello World!",{255, 255, 255}, 60),
        bind(SDL_DestroyTexture, _1)
    };

    void pre(){
        rm.gen();
    }
    void step(){}
    void render(){
        graphics.begin_render({0, 0, 0, 0});

        graphics.draw(sample_image(), 10, 10);
        graphics.draw(sample_rendered_text(), 200, 400);
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