#ifndef VEC2_HPP
#define VEC2_HPP
namespace AlGame {
struct Vec2Int {
    int x, y;

    constexpr Vec2Int(int x, int y) : x(x), y(y) {}
    /// Construct a Vec2Int with coordinate (n, n), default to (0, 0).
    explicit constexpr Vec2Int(int n = 0) : x(n), y(n) {}

    constexpr auto operator==(const Vec2Int& rhs) const -> bool { return x == rhs.x && y == rhs.y; }
    constexpr auto operator!=(const Vec2Int& rhs) const -> bool { return x != rhs.x || y != rhs.y; }

    constexpr auto operator+(const Vec2Int& rhs) const -> Vec2Int { return {x + rhs.x, y + rhs.y}; }
    constexpr auto operator-(const Vec2Int& rhs) const -> Vec2Int { return {x - rhs.x, y - rhs.y}; }
    constexpr auto operator*(const Vec2Int& rhs) const -> Vec2Int { return {x * rhs.x, y * rhs.y}; }
    constexpr auto operator/(const Vec2Int& rhs) const -> Vec2Int { return {x / rhs.x, y / rhs.y}; }

    constexpr auto operator*(int rhs) const -> Vec2Int { return {x * rhs, y * rhs}; }
    constexpr auto operator/(int rhs) const -> Vec2Int { return {x / rhs, y / rhs}; }

    constexpr auto operator+=(const Vec2Int& rhs) -> Vec2Int& {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    constexpr auto operator-=(const Vec2Int& rhs) -> Vec2Int& {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    constexpr auto operator*=(const Vec2Int& rhs) -> Vec2Int& {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }
    constexpr auto operator/=(const Vec2Int& rhs) -> Vec2Int& {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    constexpr auto operator*=(int rhs) -> Vec2Int& {
        x *= rhs;
        y *= rhs;
        return *this;
    }
    constexpr auto operator/=(int rhs) -> Vec2Int& {
        x /= rhs;
        y /= rhs;
        return *this;
    }
};

struct Vec2 {
    float x, y;

    constexpr Vec2(float x, float y) : x(x), y(y) {}
    /// Construct a Vec2 with coordinate (n, n), default to (0, 0).
    explicit constexpr Vec2(float n = 0) : x(n), y(n) {}
    explicit constexpr Vec2(const Vec2Int& v)
        : x(static_cast<float>(v.x)), y(static_cast<float>(v.y)) {}

    constexpr auto operator==(const Vec2& rhs) const -> bool { return x == rhs.x && y == rhs.y; }
    constexpr auto operator!=(const Vec2& rhs) const -> bool { return x != rhs.x || y != rhs.y; }

    constexpr auto operator+(const Vec2& rhs) const -> Vec2 { return {x + rhs.x, y + rhs.y}; }
    constexpr auto operator-(const Vec2& rhs) const -> Vec2 { return {x - rhs.x, y - rhs.y}; }
    constexpr auto operator*(const Vec2& rhs) const -> Vec2 { return {x * rhs.x, y * rhs.y}; }
    constexpr auto operator/(const Vec2& rhs) const -> Vec2 { return {x / rhs.x, y / rhs.y}; }

    constexpr auto operator*(float rhs) const -> Vec2 { return {x * rhs, y * rhs}; }
    constexpr auto operator/(float rhs) const -> Vec2 { return {x / rhs, y / rhs}; }

    constexpr auto operator+=(const Vec2& rhs) -> Vec2& {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    constexpr auto operator-=(const Vec2& rhs) -> Vec2& {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    constexpr auto operator*=(const Vec2& rhs) -> Vec2& {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }
    constexpr auto operator/=(const Vec2& rhs) -> Vec2& {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    constexpr auto operator*=(float rhs) -> Vec2& {
        x *= rhs;
        y *= rhs;
        return *this;
    }
    constexpr auto operator/=(float rhs) -> Vec2& {
        x /= rhs;
        y /= rhs;
        return *this;
    }
};
}  // namespace AlGame
#endif  // VEC2_HPP