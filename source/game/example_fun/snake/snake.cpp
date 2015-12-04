#include "game/example_fun/snake/snake.hpp"

#include <functional>
using namespace std;

Snake::Snake(
    const Body &body_segments,
    Way dir,
    Limiter limiter
): body(body_segments), direction(dir), limit(limiter){}

auto Snake::head() const -> const BodySegment &{
    return body.front();
}
auto Snake::head() -> BodySegment &{
    return body.front();
}

auto Snake::get_body() const -> const Body &{
    return body;
}

void Snake::move(){
    for(size_t i = body.size(); i--> 1;){
        body[i].x = body[i - 1].x;
        body[i].y = body[i - 1].y;
    }

    if(direction == Way::up && head().y - 1 > limit.min_y)
        head().y -= 1;
    else if(direction == Way::down && head().y + 1 < limit.max_y)
        head().y += 1;

    else if(direction == Way::left && head().x - 1 > limit.min_x)
        head().x -= 1;
    else if(direction == Way::right && head().x + 1 < limit.max_x)
        head().x += 1;
}

void Snake::grow(){
    body.push_back(head());
}

void Snake::set_direction(Way dir){
    if((int)direction != -(int)dir)
        direction = dir;
}

SnakeInputHandler::SnakeInputHandler(Snake &s):
    snake(s),
    keyboard_handler({
        {{SDLK_UP, KeyState::pressed}, bind(&Snake::set_direction, ref(snake), Way::up)},
        {{SDLK_DOWN, KeyState::pressed}, bind(&Snake::set_direction, ref(snake), Way::down)},
        {{SDLK_LEFT, KeyState::pressed}, bind(&Snake::set_direction, ref(snake), Way::left)},
        {{SDLK_RIGHT, KeyState::pressed}, bind(&Snake::set_direction, ref(snake), Way::right)},
        {{SDLK_g, KeyState::released}, bind(&Snake::grow, ref(snake))}
    })
{}