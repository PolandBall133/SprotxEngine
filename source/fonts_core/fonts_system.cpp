#include "fonts_core/fonts_system.hpp"

#include <memory>
using namespace std;
using namespace boost::filesystem;

static bool eq_color(const SDL_Color &c1, const SDL_Color &c2){
    return c1.r == c2.r && c1.g == c2.r && c1.b == c2.b && c1.a == c2.a;
}

Glyph::Glyph(TextureHandle &&tex):
    texture(move(tex)){}

SizedFont::SizedFont(GraphicsEngine &graphics_engine, FontHandle &&font_handle):
    graphics(graphics_engine),
    font(move(font_handle)){}

FontHandle::element_type *SizedFont::raw_font()
{ return font.get(); }

Glyph &SizedFont::glyph(Symbol symbol, SDL_Color color){
    auto load = [&]{ 
        return TextureHandle(
            graphics.render_text(font.get(), string(1, symbol), color),
            bind(SDL_DestroyTexture, placeholders::_1)
        );
    };

    if(!glyphs.count(symbol))
        glyphs.insert({symbol, make_unique<Glyph>(load())});
    auto &result = glyphs[symbol];
    if(!eq_color(color, result->color))
        result.reset(new Glyph(load()));
    return *glyphs[symbol];
}

const Glyph &SizedFont::glyph(Symbol symbol, SDL_Color color) const{
    auto &result = glyphs.at(symbol);
    if(!eq_color(color, result->color))
        throw std::out_of_range("color mismatch");
    return *result;
}

Font::Font(GraphicsEngine &g, const path &p):
    graphics(g),
    font_path(p){}

SizedFont &Font::of_size(size_t size){
    if(!sizes.count(size))
        sizes.insert({size, make_unique<SizedFont>(graphics, load_font(font_path, size))});
    return *sizes[size];
}

const SizedFont &Font::of_size(size_t size) const{
    return *sizes.at(size);
}


FontsSystem::FontsSystem(GraphicsEngine &graphics_engine, const boost::filesystem::path &p):
    graphics(graphics_engine),
    fonts_dir(p){}

Font &FontsSystem::font(const string &font_name){
    if(!fonts.count(font_name))
        fonts.insert({font_name, make_unique<Font>(graphics, fonts_dir + (font_name + ".ttf"))});
    return *fonts[font_name];
}

const Font &FontsSystem::font(const string &font_name) const{
    return *fonts.at(font_name);
}