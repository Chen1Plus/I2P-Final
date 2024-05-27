#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <allegro5/allegro.h>

#include <map>
#include <memory>
#include <string>

#include "scene.hpp"
#include "vec2.hpp"

namespace AlGame {
class Engine {
    Engine() = default;
    // screen config
    const int fps = 60;
    Vec2Int screenSize;
    // screen resources
    std::shared_ptr<ALLEGRO_DISPLAY> display;
    std::shared_ptr<ALLEGRO_EVENT_QUEUE> eventQueue;
    std::shared_ptr<ALLEGRO_TIMER> timer;
    // scenes
    std::map<std::string, std::unique_ptr<Scene>> scenes;
    std::string currentScene;

    static void initialize();

   public:
    Engine(Engine const&)                    = delete;
    auto operator=(Engine const&) -> Engine& = delete;
    static auto getInstance() -> Engine&;

    void createWindow(const char* title, Vec2Int size);
    void addScene(std::string name, std::unique_ptr<Scene>);
    void changeScene(std::string name);
    void run();
};
}  // namespace AlGame
#endif  // ENGINE_HPP