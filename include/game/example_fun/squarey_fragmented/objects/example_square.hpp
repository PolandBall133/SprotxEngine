#pragma once
#include "../core/game_object.hpp"

struct Color{
    uint8_t r, g, b, a;
};
struct ExampleSquare: GameObject{
    size_t size;
    Color color;

    ExampleSquare(size_t s, Color c):
        size(s), color(c){}
};