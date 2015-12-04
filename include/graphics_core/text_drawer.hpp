#pragma once

#include "fonts_core/fonts_system.hpp"
#include "graphics_engine.hpp"

#include <string>

struct TextDrawer{
    GraphicsEngine &graphics;

    TextDrawer(GraphicsEngine &graphics);

    void draw(
        SizedFont &font,
        const std::string &text, 
        int x, int y,
        size_t space = 0, 
        SDL_Color color = {0, 0, 0});
};