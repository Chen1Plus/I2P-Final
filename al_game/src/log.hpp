#ifndef LOG_HPP
#define LOG_HPP

#include <spdlog/spdlog.h>

#include <memory>

/// AlGame::Log provides the logging context for the entire library.
namespace AlGame::Log {
/// The logger instance.
inline std::unique_ptr<spdlog::logger> Slog;
/// The path to the log file.
inline const auto PATH = "logs/AlGame.log";
/// Initialize the logger. Safe to call multiple times, but usually done once at program start.
void initialize();
}  // namespace AlGame::Log
#endif