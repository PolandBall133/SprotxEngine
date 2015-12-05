#pragma once

#include "graphics_core/graphics_engine.hpp"
#include "resources_managment/font.hpp"
#include "resources_managment/texture.hpp"

#include "utility/path_utils.hpp"

#include <unordered_map>
#include <string>

struct Glyph;
class SizedFont;
class Font;
class FontsSystemInstance;

struct Glyph{
    TextureHandle texture;
    const SDL_Color color;
    Glyph(TextureHandle &&texture);
};

class SizedFont{
public:
    using Symbol = char;
private:
    GraphicsEngine &graphics;
    FontHandle font;
    std::unordered_map<Symbol, std::unique_ptr<Glyph>> glyphs;
public:
    SizedFont(GraphicsEngine &graphics_engine, FontHandle &&font_handle);
    FontHandle::element_type *raw_font();
    Glyph &glyph(Symbol symbol, SDL_Color color = {0, 0, 0, 0});
    const Glyph &glyph(Symbol symbol, SDL_Color color = {0, 0, 0, 0}) const;
};

class Font{
private:
    GraphicsEngine &graphics;
    boost::filesystem::path font_path;
    std::unordered_map<size_t, std::unique_ptr<SizedFont>> sizes;
public:
    Font(GraphicsEngine &g, const boost::filesystem::path &p);
    SizedFont &of_size(size_t size);
    const SizedFont &of_size(size_t size) const;
};

class FontsSystem{
private:
    std::unordered_map<std::string, std::unique_ptr<Font>> fonts;
    GraphicsEngine &graphics;
    boost::filesystem::path fonts_dir;
public:
    FontsSystem(GraphicsEngine &graphics_engine, const boost::filesystem::path &p);
    Font &font(const std::string &font_name);
    const Font &font(const std::string &font_name) const;
};