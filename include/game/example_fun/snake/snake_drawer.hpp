#pragma once
#include "graphics_core/graphics_engine.hpp"
#include "snake.hpp"

#include "resources_managment/texture.hpp"

struct SnakeDrawer{
    GraphicsEngine &graphics;
    const Snake &snake;
    RawCAPIResource<SDL_Texture> &segment_tex;

    SnakeDrawer(GraphicsEngine &g, const Snake &s, RawCAPIResource<SDL_Texture> &s_tex);
    void draw();

    void initialize();
    void finalize();
};
