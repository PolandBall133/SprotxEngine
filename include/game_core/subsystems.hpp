#pragma once
#include <boost/logic/tribool.hpp>

#include "game_engine.hpp"

void init(GameEngine &engine);
boost::tribool init_internal_subsystems(GameEngine &engine, uint32_t flags);