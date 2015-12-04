#include "fonts_core/fonts_system.hpp"

#include <memory>
using namespace std;
using namespace boost::filesystem;

Glyph::Glyph(TextureHandle &&tex):
    texture(move(tex)){}

SizedFont::SizedFont(GraphicsEngine &graphics_engine, FontHandle &&font_handle):
    graphics(graphics_engine),
    font(move(font_handle)){}

FontHandle::element_type *SizedFont::raw_font()
{ return font.get(); }

Glyph &SizedFont::glyph(Symbol symbol){
    if(!glyphs.count(symbol))
        glyphs.insert(
            {symbol, make_unique<Glyph>(
                RawCAPIResource<SDL_Texture>(
                    graphics.render_text(font.get(), string(1, symbol), {}),
                    bind(SDL_DestroyTexture, placeholders::_1)
            ))});
    return *glyphs[symbol];
}

const Glyph &SizedFont::glyph(Symbol symbol) const{
    return *glyphs.at(symbol);
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