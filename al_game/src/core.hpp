#ifndef CORE_HPP
#define CORE_HPP

#include <spdlog/spdlog.h>

#include <memory>

/// AlGame::Core provides the basic context for the entire library.
/// Any global variables in this scope must be used as read only to ensure security.
namespace AlGame::Core {
/// Logger
inline std::unique_ptr<spdlog::logger> Slog;

void initialize();
}  // namespace AlGame::Core
#endif  // CORE_HPP