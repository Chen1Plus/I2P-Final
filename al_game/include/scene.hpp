#ifndef SCENE_HPP
#define SCENE_HPP

#include <cstdint>

#include "vec2.hpp"

namespace AlGame {
class Scene {
   public:
    virtual ~Scene()                       = default;
    virtual void update(int64_t deltaTime) = 0;
    virtual void draw()                    = 0;

    virtual void onKeyDown(int keyCode) {};
    virtual void onKeyUp(int keyCode) {};
    virtual void onMouseDown(unsigned btn, Vec2Int pos) {};
    virtual void onMouseUp(unsigned btn, Vec2Int pos) {};
    virtual void onMouseMove(Vec2Int pos) {};
    virtual void onMouseScroll(Vec2Int pos, int delta) {};
};
}  // namespace AlGame
#endif  // SCENE_HPP