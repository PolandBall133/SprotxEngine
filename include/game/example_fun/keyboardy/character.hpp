#pragma once

struct Character{
    struct Position{
        int x, y;
    } pos;

    Character(const Position &p): pos(p){}
};