#ifndef RECT_HPP
#define RECT_HPP
#include "vec2.hpp"
namespace AlGame {
struct Rect {
    Vec2 pos, size;

    constexpr Rect(Vec2 pos, Vec2 size) : pos(pos), size(size) {}

    [[nodiscard]] constexpr auto overlaps(const Rect& rect) const -> bool {
        return pos.x < rect.pos.x + rect.size.x && pos.x + size.x > rect.pos.x &&
               pos.y < rect.pos.y + rect.size.y && pos.y + size.y > rect.pos.y;
    }
};
}  // namespace AlGame
#endif