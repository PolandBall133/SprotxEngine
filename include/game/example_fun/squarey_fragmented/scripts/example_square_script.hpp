#pragma once
#include "../objects/example_square.hpp"
#include "boost/log/trivial.hpp"
struct ExampleSquareScript: Script{
    using this_class = ExampleSquareScript;
    SCRIPT_INIT_METHODS(this_class, pre, step, render, post);

    ExampleSquare *square;

    void pre(){
        BOOST_LOG_TRIVIAL(info) << "Hello World!";
        square = static_cast<ExampleSquare*>(attached_object);
        
        square->transform.position.x = 100;
        square->transform.position.y = 100;
    }

    void step(){}

    void render(){
        auto halved_size = square->size / 2;
        auto pos = square->transform.position;
        auto col = square->color;
        
        SDL_Color color = {col.r, col.g, col.b, col.a};
        for(int i = -5; i <= 5; ++i){
            SDL_Rect rect = {
                static_cast<int>(pos.x - halved_size+i), static_cast<int>(pos.y - halved_size+i),
                static_cast<int>(pos.x + halved_size+i), static_cast<int>(pos.y + halved_size+i)
            };
            graphics_engine->draw(rect, {0, 0, 0});
        }
    }
    void post(){}
};