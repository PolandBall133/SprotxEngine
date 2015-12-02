#include "game/example_fun/snake/fruits_drawer.hpp"

FruitsDrawer::FruitsDrawer(GraphicsEngine &g, FruitsManager &m, TextureHandle &f_tex):
    graphics(g),
    fruits(m),
    fruit_tex(f_tex)
{}

void FruitsDrawer::draw(){
    const size_t count = fruits.count();
    for(size_t i = 0; i < count; ++i){
        auto fruit = fruits.at(i);
        graphics.draw(fruit_tex.get(), fruit.x*10, fruit.y*10);
    }
}