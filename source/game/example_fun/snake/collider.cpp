#include "game/example_fun/snake/collider.hpp"

Collider::Collider(FruitsManager &fm, ScoreManager &sm, Snake &s, YSE::sound &eating_snd):
    fruits_manager(fm),
    score_manager(sm),
    snake(s),
    eating_sound(eating_snd)
{}

void Collider::check_and_react(){
    auto head = snake.head();
    FruitsManager::Fruit fruit = { head.x, head.y };
    while(fruits_manager.contains(fruit)){
        fruits_manager.remove(fruit);
        score_manager.add_points(1);

        snake.grow();

        eating_sound.setTime(0);
        eating_sound.play();
    }
}