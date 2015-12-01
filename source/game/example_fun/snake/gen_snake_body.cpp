#include "game/example_fun/snake/gen_snake_body.hpp"

Snake::Body gen_snake_body(){
    const size_t segments_count = 40;
    Snake::Body result;
    for(int i = 1; i <= segments_count; ++i)
        result.push_back({1, i});
    return result;
}