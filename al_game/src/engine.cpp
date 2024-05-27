#include "engine.hpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <memory>
#include <string>
#include <utility>

#include "asset.hpp"
#include "error.hpp"
#include "log.hpp"
#include "vec2.hpp"

using AlGame::Engine;
using AlGame::Log::Slog;
using std::shared_ptr;

static bool Initialized = false;
void Engine::initialize() {
    if (Initialized) return;

    AlGame::Log::initialize();
    AlGame::Asset::initialize();

    // Allegro initialization.
    if (al_init() && al_init_primitives_addon() && al_init_image_addon() && al_init_font_addon() &&
        al_init_ttf_addon() && al_install_audio() && al_init_acodec_addon() &&
        al_install_keyboard() && al_install_mouse() && al_reserve_samples(1000)) {
        // Enable antialias by linear interpolation.
        al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
        Slog->debug("Allegro initialized");
    } else {
        throw Error("Allegro initialization failed");
    }

    Initialized = true;
    Slog->info("Engine initialized");
}

auto Engine::instance() -> Engine& {
    initialize();
    static Engine Instance;
    return Instance;
}

void Engine::createWindow(const char* title, Vec2Int size) {
    Slog->info("Creating window: \"{}\" with size {}x{}", title, size.x, size.y);
    screenSize = size;

    display    = shared_ptr<ALLEGRO_DISPLAY>(al_create_display(size.x, size.y), al_destroy_display);
    eventQueue = shared_ptr<ALLEGRO_EVENT_QUEUE>(al_create_event_queue(), al_destroy_event_queue);
    timer      = shared_ptr<ALLEGRO_TIMER>(al_create_timer(1.0 / fps), al_destroy_timer);
    if (display == nullptr) throw Error("Failed to create display");
    if (eventQueue == nullptr) throw Error("Failed to create event queue");
    if (timer == nullptr) throw Error("Failed to create timer");

    al_set_window_title(display.get(), title);
    al_register_event_source(eventQueue.get(), al_get_display_event_source(display.get()));
    al_register_event_source(eventQueue.get(), al_get_timer_event_source(timer.get()));
    al_register_event_source(eventQueue.get(), al_get_keyboard_event_source());
    al_register_event_source(eventQueue.get(), al_get_mouse_event_source());
    al_start_timer(timer.get());
}

void Engine::addScene(std::string name, std::unique_ptr<Scene> scene) {
    Slog->info("Add scene: \"{}\"", name);
    scenes.insert({std::move(name), std::move(scene)});
}

void Engine::changeScene(const std::string& name) {
    if (scenes.contains(name)) {
        Slog->info("Change scene to \"{}\"", name);
        nextScene = name;
    } else
        throw Error("Scene \"" + name + "\" not found");
}

void Engine::run(const std::string& firstScene) {
    Slog->info("Start looping");
    bool done    = false;
    int redraws  = 0;
    currentScene = firstScene;
    nextScene    = firstScene;

    ALLEGRO_EVENT event;
    auto timestamp = std::chrono::steady_clock::now();
    while (!done) {
        currentScene = nextScene;
        al_wait_for_event(eventQueue.get(), &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                Slog->trace("Window close button clicked");
                done = true;
                break;

            // Event for redrawing the display.
            case ALLEGRO_EVENT_TIMER:
                if (event.timer.source == timer.get()) redraws++;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                Slog->trace("Key with keycode {} down", event.keyboard.keycode);
                scenes[currentScene]->onKeyDown(event.keyboard.keycode);
                break;

            case ALLEGRO_EVENT_KEY_UP:
                Slog->trace("Key with keycode {} up", event.keyboard.keycode);
                scenes[currentScene]->onKeyUp(event.keyboard.keycode);
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                // Event for mouse key down.
                Slog->trace("Mouse button {} down at ({}, {})", event.mouse.button, event.mouse.x,
                            event.mouse.y);
                scenes[currentScene]->onMouseDown(event.mouse.button,
                                                  {event.mouse.x, event.mouse.y});
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:

                Slog->trace("Mouse button {} up at ({}, {})", event.mouse.button, event.mouse.x,
                            event.mouse.y);
                scenes[currentScene]->onMouseUp(event.mouse.button, {event.mouse.x, event.mouse.y});
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                if (event.mouse.dx != 0 || event.mouse.dy != 0) {
                    // Event for mouse move.
                    Slog->trace("Mouse move to ({}, {})", event.mouse.x, event.mouse.y);
                    scenes[currentScene]->onMouseMove({event.mouse.x, event.mouse.y});
                } else if (event.mouse.dz != 0) {
                    // Event for mouse scroll.
                    Slog->trace("Mouse scroll at ({}, {}) with delta {}", event.mouse.x,
                                event.mouse.y, event.mouse.dz);
                    scenes[currentScene]->onMouseScroll({event.mouse.x, event.mouse.y},
                                                        event.mouse.dz);
                }
                break;

            case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
                Slog->trace("Mouse leave display.");
                scenes[currentScene]->onMouseMove(Vec2Int(-1));
                break;

            case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY: Slog->trace("Mouse enter display."); break;

            // ignore other events
            default: break;
        }

        // Redraw the scene.
        if (redraws > 0 && al_is_event_queue_empty(eventQueue.get())) {
            if (redraws > 1) Slog->warn("Frame drop: {}", redraws - 1);

            // Calculate the timeElapsed and update the timestamp.
            auto nextTimestamp = std::chrono::steady_clock::now();
            auto timeElapsed   = nextTimestamp - timestamp;
            timestamp          = nextTimestamp;
            // Update and draw the next frame.
            scenes[currentScene]->update(timeElapsed.count());
            al_clear_to_color(al_map_rgb(0, 0, 0));
            scenes[currentScene]->draw();
            al_flip_display();
            redraws = 0;
        }
    }
    Slog->info("Stop looping");
}