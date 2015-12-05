#include "graphics_core/text_drawer.hpp"
#include "boost/log/trivial.hpp"
using namespace std;

TextDrawer::TextDrawer(GraphicsEngine &g):
    graphics(g){}

void TextDrawer::draw(
    SizedFont &font,
    const string &text, 
    int x, int y,
    size_t space,
    SDL_Color color)
{
    for(size_t i = 0; i < text.size(); ++i){
        auto &tex = font.glyph(text[i], color).texture;

        int minx, maxx, miny, maxy, advance;
        if(TTF_GlyphMetrics(font.raw_font(), 'g', &minx, &maxx, &miny, &maxy, &advance) == -1)
            BOOST_LOG_TRIVIAL(error) << TTF_GetError();

        x += (advance + space);
        graphics.draw(tex.get(), x, y);
    }
}