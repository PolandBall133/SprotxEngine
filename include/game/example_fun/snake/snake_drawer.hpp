#pragma once
#include "graphics_core/graphics_engine.hpp"
#include "snake.hpp"

#include "resources_managment/texture.hpp"

struct SnakeDrawer{
    GraphicsEngine &graphics;
    const Snake &snake;
    TextureHandle &segment_tex;

    SnakeDrawer(GraphicsEngine &g, const Snake &s, TextureHandle &s_tex);
    void draw();
};
