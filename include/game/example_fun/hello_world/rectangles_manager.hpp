#pragma once

#include "game_core/defines.hpp"
#include "SDL.h"

#include <vector>
#include <random>
struct RectanglesManager{
    struct ColoredRect{
        SDL_Rect rect;
        SDL_Color color;
    };
    std::vector<ColoredRect> rects;
    void gen(){
        std::default_random_engine gen;
        std::uniform_int_distribution<> width(1, 640), height(1, 480), color(0, 255);
        for(size_t i = 0; i < 200; ++i)
            rects.push_back(ColoredRect{
                {height(gen), width(gen), height(gen), width(gen)},
                {(Uint8) color(gen), (Uint8) color(gen), (Uint8) color(gen), (Uint8) color(gen)}
        });
    }
};