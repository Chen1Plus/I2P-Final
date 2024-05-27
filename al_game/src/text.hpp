#ifndef TEXT_HPP
#define TEXT_HPP

#include <allegro5/allegro_font.h>

#include <memory>
#include <string>

#include "vec2.hpp"

namespace AlGame {
class Text {
    std::shared_ptr<ALLEGRO_FONT> font;
    ALLEGRO_COLOR font_color;
    // content and its size
    std::string str;
    Vec2Int size;

   public:
    explicit Text(const char* s, int fontSize, const char* font = "pirulen.ttf");

    auto color(int r, int g, int b) -> Text&;
    void draw(Vec2 pos, Vec2 anchor = {0.5, 0.5}) const;
};
}  // namespace AlGame
#endif  // TEXT_HPP