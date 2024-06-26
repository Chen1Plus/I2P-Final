#include "log.hpp"

#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <fstream>
#include <memory>

void AlGame::Log::initialize() {
    using namespace spdlog;
    std::ofstream ofs(PATH, std::ios::out);
    ofs.close();
    Slog = std::make_unique<logger>(
        logger("AlGame", {std::make_shared<sinks::stdout_color_sink_st>(),
                          std::make_shared<sinks::basic_file_sink_st>(PATH)}));
#ifdef _DEBUG
    Slog->set_level(level::trace);
#else
    Slog->set_level(level::info);
#endif
    Slog->set_pattern("[%m-%d %H:%M:%S] %^[%l]%$ %v");
    Slog->trace("Logger initialized");
}