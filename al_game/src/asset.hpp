#ifndef ASSET_HPP
#define ASSET_HPP

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include <memory>

#include "vec2.hpp"

namespace AlGame::Asset {
inline auto* FontPath   = "assets/fonts/";
inline auto* BitmapPath = "assets/images/";
inline auto* SamplePath = "assets/sounds/";

void initialize();

auto getFont(const char* name, int size) -> std::shared_ptr<ALLEGRO_FONT>;
auto getBitmap(const char* name) -> std::shared_ptr<ALLEGRO_BITMAP>;
auto getBitmap(const char* name, Vec2Int size) -> std::shared_ptr<ALLEGRO_BITMAP>;
auto getSample(const char* name) -> std::shared_ptr<ALLEGRO_SAMPLE>;
}  // namespace AlGame::Asset
#endif  // ASSET_HPP