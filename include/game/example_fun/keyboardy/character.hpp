#pragma once

#include <functional>

struct Character{
    struct Position{
        int x, y;
    } pos;

    void move_x(int x){
        pos.x += x;
    }
    void move_y(int y){
        pos.y += y;
    }
    std::function<void()> move, post_move;

    Character(const Position &p, std::function<void()> &&ac): pos(p), post_move(ac){}

    void update(){
        if(move){
            move();
            post_move();
        }
    }
};