#include "game/example_fun/snake/snake_drawer.hpp"

SnakeDrawer::SnakeDrawer(GraphicsEngine &g, const Snake &s, RawCAPIResource<SDL_Texture> &s_tex): 
    graphics(g), snake(s),
    segment_tex(s_tex){}

void SnakeDrawer::draw(){
    for(auto &element : snake.get_body()){
        int big_x = element.x * 10, big_y = element.y * 10;
        graphics.draw(segment_tex.get(), big_x, big_y);
    }
}