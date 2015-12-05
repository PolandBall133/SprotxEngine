#pragma once

#include "fruits_manager.hpp"
#include "snake.hpp"

#include "score_manager.hpp"
#include "yse/yse.hpp"

struct Collider{
    FruitsManager &fruits_manager;
    ScoreManager &score_manager;
    Snake &snake;
    YSE::sound &eating_sound;
    Collider(FruitsManager &fm, ScoreManager &sm, Snake &s, YSE::sound &eating_snd);

    void check_and_react();
};