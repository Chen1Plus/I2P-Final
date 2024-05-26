#ifndef ERROR_HPP
#define ERROR_HPP
#include <stdexcept>
namespace AlGame {
class Error final : std::runtime_error {
   public:
    explicit Error(const char* msg) noexcept;
    explicit Error(const std::string& msg) noexcept;
};
}  // namespace AlGame
#endif  // ERROR_HPP