#include "engine.hpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <memory>

#include "asset.hpp"
#include "error.hpp"
#include "log.hpp"
#include "vec2.hpp"

using AlGame::Engine;
using AlGame::Log::Slog;
using std::shared_ptr;

void Engine::initialize() {
    if (initialized) return;

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

    initialized = true;
}

auto Engine::getInstance() -> Engine& {
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

auto Engine::getEvent() -> ALLEGRO_EVENT {
    ALLEGRO_EVENT event;
    al_wait_for_event(eventQueue.get(), &event);
    return event;
}