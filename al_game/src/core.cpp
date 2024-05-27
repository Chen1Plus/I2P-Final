#include "core.hpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <fstream>
#include <memory>

#include "error.hpp"

void AlGame::Core::initialize() {
    // Slog initialization
    {
        using namespace spdlog;
        std::ofstream ofs("logs/AlGame.log", std::ios::out);
        ofs.close();
        Slog = std::make_unique<logger>(
            logger("AlGame", {std::make_shared<sinks::stdout_color_sink_st>(),
                              std::make_shared<sinks::basic_file_sink_st>("logs/AlGame.log")}));
#ifdef _DEBUG
        Slog->set_level(level::trace);
#else
        Slog->set_level(level::info);
#endif
        Slog->set_pattern("[%m-%d %H:%M:%S] %^[%l]%$ %v");
        Slog->trace("Logger initialized");
    }

    // Allegro initialization
    if (al_init() && al_init_primitives_addon() && al_init_image_addon() && al_init_font_addon() &&
        al_init_ttf_addon() && al_install_audio() && al_init_acodec_addon() &&
        al_install_keyboard() && al_install_mouse() && al_reserve_samples(RESERVE_SAMPLES)) {
        // Enable antialias by linear interpolation.
        al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
        Slog->debug("Allegro initialized");
    } else {
        throw Error("Allegro initialization failed");
    }
}