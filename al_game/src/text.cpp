#include "text.hpp"

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "asset.hpp"
#include "error.hpp"
#include "vec2.hpp"

using AlGame::Text;

Text::Text(const char* s, int fontSize, const char* font) : str(s) {
    this->font = Asset::getFont(font, fontSize);
    font_color = al_map_rgb(0, 0, 0);
    size = {al_get_text_width(this->font.get(), s), al_get_font_line_height(this->font.get())};
}

auto Text::color(int r, int g, int b) -> Text& {
    font_color = al_map_rgb(r, g, b);
    return *this;
}

void Text::draw(Vec2 pos, Vec2 anchor) const {
    pos -= Vec2(size) * anchor;
    al_draw_text(font.get(), font_color, pos.x, pos.y, 0, str.c_str());
}