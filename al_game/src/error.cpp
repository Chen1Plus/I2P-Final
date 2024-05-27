#include "error.hpp"

#include <stdexcept>

#include "log.hpp"

inline AlGame::Error::Error(const char* msg) noexcept : std::runtime_error(msg) {
    AlGame::Log::Slog->critical(msg);
}

inline AlGame::Error::Error(const std::string& msg) noexcept : AlGame::Error(msg.c_str()) {}
