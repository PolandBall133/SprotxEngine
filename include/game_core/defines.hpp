#pragma once
#include <string>
#include <map>

using SettingsMap = std::map<std::string, std::string>;

#define SDL_MAIN_HANDLED
#define INIT_EVERYTHING SDL_INIT_EVERYTHING

#define DEF_CONSTEXPR_STR_LITERAL(name) constexpr const char *name = #name