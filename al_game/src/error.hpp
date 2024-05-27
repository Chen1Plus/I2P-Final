#ifndef ERROR_HPP
#define ERROR_HPP

#include <stdexcept>

#include "log.hpp"

namespace AlGame {
class Error final : std::runtime_error {
   public:
    explicit Error(const char* msg) noexcept : std::runtime_error(msg) {
        AlGame::Log::Slog->critical(msg);
    }
    explicit Error(const std::string& msg) noexcept : Error(msg.c_str()) {};
};
}  // namespace AlGame
#endif  // ERROR_HPP