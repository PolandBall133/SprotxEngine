#pragma once

#include "example_square_connection.hpp"

template<typename Scene>
void attach_connections_to_scene(Scene &scene){
    add_example_square_connection(scene);
}