#pragma once
#include <boost/logic/tribool.hpp>

#include "defines.hpp"
#include "game_engine.hpp"

void init(GameEngine &engine, const SettingsMap &settings);

void finish(GameEngine &engine);

boost::tribool init_internal_subsystems(GameEngine &engine, const SettingsMap &settings);

boost::tribool init_internal_subsystems(GameEngine &engine, uint32_t flags);

void init_window(GameEngine &engine, const SettingsMap &settings);

void init_window(GameEngine &engine, size_t width, size_t height, const char *title);

void init_renderer(GameEngine &engine);