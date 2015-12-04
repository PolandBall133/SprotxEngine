#pragma once
#include <vector>

#include "game_core/helpers/mapping_keyboard_handler.hpp"

#include "limiter.hpp"

enum class Way{ 
    none, 
    up = 1, down = -1, 
    left = 2, right = -2
};

class Snake{
public:
    using BodySegment = struct{ int x, y; };
    using Body = std::vector<BodySegment>;
public:
    Snake(const Body &body_segments, Way dir, Limiter limiter);
    const BodySegment &head() const;
    BodySegment &head();
    const Body &get_body() const;
    void move();
    void grow();
    void set_direction(Way);
private:
    Way direction;
    Body body;
    Limiter limit;
};

struct SnakeInputHandler{
    Snake &snake;
    MappingKeyboardHandler keyboard_handler;
    SnakeInputHandler(Snake &s);
};