#include "game/example_fun/snake/collider.hpp"

Collider::Collider(FruitsManager &fm, Snake &s):
    fruits_manager(fm),
    snake(s)
{}

void Collider::check_and_react(){
    auto head = snake.head();
    FruitsManager::Fruit fruit = { head.x, head.y };
    while(fruits_manager.contains(fruit)){
        fruits_manager.remove(fruit);
        snake.grow();
    }
}