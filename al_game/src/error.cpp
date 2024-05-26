#include "error.hpp"

#include <stdexcept>

#include "core.hpp"

inline AlGame::Error::Error(const char* msg) noexcept : std::runtime_error(msg) {
    AlGame::Core::Slog->critical(msg);
}

inline AlGame::Error::Error(const std::string& msg) noexcept : std::runtime_error(msg) {
    AlGame::Core::Slog->critical(msg);
}