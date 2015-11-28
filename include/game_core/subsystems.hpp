#pragma once
#include <boost/logic/tribool.hpp>

#include "defines.hpp"
#include "game_engine.hpp"

void init(GameEngine &engine, const SettingsMap &settings);

boost::tribool init_internal_subsystems(GameEngine &engine, const SettingsMap &settings);

boost::tribool init_internal_subsystems(GameEngine &engine, uint32_t flags);

void init_window_data(GameEngine &engine, const SettingsMap &settings);