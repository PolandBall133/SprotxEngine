#pragma once
#include <boost/logic/tribool.hpp>

#include "game_engine.hpp"

boost::tribool init_subsystems(GameEngine &engine, uint32_t flags);