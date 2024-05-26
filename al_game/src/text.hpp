#ifndef TEXT_HPP
#define TEXT_HPP
#include <string>
#include <utility>
namespace AlGame {
class Text {
    std::string str;

   public:
    explicit Text(const char* s) : str(s) {};
    explicit Text(std::string s) : str(std::move(s)) {};
};
}  // namespace AlGame
#endif  // TEXT_HPP