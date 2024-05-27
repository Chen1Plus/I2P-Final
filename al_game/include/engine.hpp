#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <allegro5/allegro.h>

#include <memory>

#include "vec2.hpp"

namespace AlGame {
class Engine {
    Engine()                       = default;
    inline static bool initialized = false;

    // screen config
    const int fps = 60;
    Vec2Int screenSize;

    // screen resources
    std::shared_ptr<ALLEGRO_DISPLAY> display;
    std::shared_ptr<ALLEGRO_EVENT_QUEUE> eventQueue;
    std::shared_ptr<ALLEGRO_TIMER> timer;

    static void initialize();

   public:
    Engine(Engine const&)                    = delete;
    auto operator=(Engine const&) -> Engine& = delete;

    static auto getInstance() -> Engine&;
    void createWindow(const char* title, Vec2Int size);
    auto getEvent() -> ALLEGRO_EVENT;
};
}  // namespace AlGame
#endif  // ENGINE_HPP