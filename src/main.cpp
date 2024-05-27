#include "engine.hpp"

auto main() -> int {
    auto &game = AlGame::Engine::getInstance();

    game.createWindow("Hello, World!", {800, 600});
    while (game.getEvent().type != ALLEGRO_EVENT_DISPLAY_CLOSE) {}
}