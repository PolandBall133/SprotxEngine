#pragma once

#include "../core/scene.hpp"
#include "../scripts/example_square_script.hpp"

template<typename Scene>
void add_example_square_connection(Scene &scene){
    GameObject *object = new ExampleSquare(100, {255, 0, 30, 100});
    Script *script = Script::spawn_attached_to<ExampleSquareScript>(object, &scene.engine, &scene.graphics);
    scene.register_object(object);
    scene.scripts.register_script(script);
}