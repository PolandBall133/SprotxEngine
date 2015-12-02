#pragma once

#include "fruits_manager.hpp"

#include "graphics_core/graphics_engine.hpp"
#include "resources_managment/texture.hpp"

struct FruitsDrawer{
    GraphicsEngine &graphics;
    FruitsManager &fruits;
    TextureHandle &fruit_tex;

    FruitsDrawer(GraphicsEngine &g, FruitsManager &m, TextureHandle &f_tex);
    void draw();
};