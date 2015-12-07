#pragma once
#include "game_object.hpp"
#include "game_core/game_engine.hpp"
#include "graphics_core/graphics_engine.hpp"
struct Scene: GameObjectsContainer{
    ScriptsContainer scripts;
    GameEngine &engine;
    GraphicsEngine &graphics;

    Scene(GameEngine &e, GraphicsEngine &ge):
        engine(e),
        graphics(ge){}
};