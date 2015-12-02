#pragma once
#include <vector>

enum class Way{ 
    none, 
    up = 1, down = -1, 
    left = 2, right = -2
};

class Snake{
public:
    using BodySegment = struct{ int x, y; };
    using Body = std::vector<BodySegment>;
    struct Limiter{
        int min_x, min_y, max_x, max_y;
    };
public:
    Snake(const Body &body_segments, Way dir, Limiter limiter);
    const BodySegment &head() const;
    BodySegment &head();
    const Body &get_body() const;
    void move();
    void set_direction(Way);
private:
    Way direction;
    Body body;
    Limiter limit;
};