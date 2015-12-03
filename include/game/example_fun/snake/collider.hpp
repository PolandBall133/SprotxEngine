#pragma once

#include "fruits_manager.hpp"
#include "snake.hpp"

#include "yse/yse.hpp"

struct Collider{
    FruitsManager &fruits_manager;
    Snake &snake;
    YSE::sound &eating_sound;
    Collider(FruitsManager &fm, Snake &s, YSE::sound &eating_snd);

    void check_and_react();
};