#pragma once
#include <string>
#include <map>
#include <cctype>

using SettingsMap = std::map<std::string, std::string>;

#define SDL_MAIN_HANDLED
#define INIT_EVERYTHING SDL_INIT_EVERYTHING

#define DEF_CONSTEXPR_STR_LITERAL_K(name) constexpr const char *name = #name
#define DEF_CONSTEXPR_STR_LITERAL_V(name, val) constexpr const char *name = val