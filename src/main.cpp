#include <iostream>

#include "engine.hpp"
#include "text.hpp"

class MyScene : public AlGame::Scene {
   public:
    void update(int64_t deltaTime) override {}
    void draw() override {
        AlGame::Text("Hello, World!", 48).color(255, 255, 255).draw({200, 200});
    }
};

auto main() -> int {
    auto &game = AlGame::Engine::instance();
    game.createWindow("HaHa", {800, 600});

    game.addScene("MyScene", std::make_unique<MyScene>());
    game.run("MyScene");
}