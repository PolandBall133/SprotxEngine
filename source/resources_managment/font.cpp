#include "resources_managment/font.hpp"

RawCAPIResource<TTF_Font> load_font(const boost::filesystem::path &p, size_t size){
    auto internal = boost::filesystem::is_regular_file(p) ?
        TTF_OpenFont(p.string().c_str(), size) : nullptr;

    RawCAPIResource<TTF_Font> result{
        internal,
        std::bind(TTF_CloseFont, std::placeholders::_1)
    };

    return result;
}