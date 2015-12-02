#pragma once

#include "fruits_manager.hpp"
#include "snake.hpp"

struct Collider{
    FruitsManager &fruits_manager;
    Snake &snake;
    Collider(FruitsManager &fm, Snake &s);

    void check_and_react();
};