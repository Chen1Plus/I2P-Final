#include "asset.hpp"

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include <map>
#include <memory>
#include <string>

#include "core.hpp"
#include "error.hpp"
#include "vec2.hpp"

using AlGame::Error;
using AlGame::Core::Slog;
using std::map;
using std::shared_ptr;
using std::string;
using std::to_string;

static std::unique_ptr<map<string, shared_ptr<ALLEGRO_FONT>>> Fonts;
static std::unique_ptr<map<string, shared_ptr<ALLEGRO_BITMAP>>> Bitmaps;
static std::unique_ptr<map<string, shared_ptr<ALLEGRO_SAMPLE>>> Samples;

void AlGame::Asset::initialize() {
    Fonts   = std::make_unique<map<string, shared_ptr<ALLEGRO_FONT>>>();
    Bitmaps = std::make_unique<map<string, shared_ptr<ALLEGRO_BITMAP>>>();
    Samples = std::make_unique<map<string, shared_ptr<ALLEGRO_SAMPLE>>>();
    Slog->trace("Assets manager initialized");
}

auto AlGame::Asset::getFont(const char* name, int size) -> shared_ptr<ALLEGRO_FONT> {
    const auto path = string(name) + '?' + to_string(size);
    if (Fonts->contains(path)) return Fonts->at(path);
    Slog->debug("Asset<Font> Loading {}", path);

    auto ft = shared_ptr<ALLEGRO_FONT>(al_load_font((string(FontPath) + path).c_str(), size, 0),
                                       al_destroy_font);
    if (ft == nullptr) throw Error("Asset<Font> Failed to load " + path);
    Fonts->insert({path, ft});
    return ft;
}

auto AlGame::Asset::getBitmap(const char* name) -> shared_ptr<ALLEGRO_BITMAP> {
    if (Bitmaps->contains(name)) return Bitmaps->at(name);
    Slog->debug("Asset<Bitmap> Loading {}", name);

    auto bmp = shared_ptr<ALLEGRO_BITMAP>(al_load_bitmap((string(BitmapPath) + name).c_str()),
                                          al_destroy_bitmap);
    if (bmp == nullptr) throw Error("Asset<Bitmap> Failed to load " + string(name));
    Bitmaps->insert({name, bmp});
    return bmp;
}

auto AlGame::Asset::getBitmap(const char* name, Vec2Int size) -> shared_ptr<ALLEGRO_BITMAP> {
    const auto path = string(name) + '?' + to_string(size.x) + 'x' + to_string(size.y);
    if (Bitmaps->contains(path)) return Bitmaps->at(path);
    Slog->debug("Asset<Bitmap> Loading {}", path);

    auto bmp    = getBitmap(name);
    auto newBmp = shared_ptr<ALLEGRO_BITMAP>(al_create_bitmap(size.x, size.y), al_destroy_bitmap);
    if (newBmp == nullptr) throw Error("Asset<Bitmap> Failed to create bitmap");

    auto* prevTarget = al_get_target_bitmap();
    al_set_target_bitmap(newBmp.get());
    al_draw_scaled_bitmap(bmp.get(), 0, 0, static_cast<float>(al_get_bitmap_width(bmp.get())),
                          static_cast<float>(al_get_bitmap_height(bmp.get())), 0, 0,
                          static_cast<float>(size.x), static_cast<float>(size.y), 0);
    al_set_target_bitmap(prevTarget);

    Bitmaps->insert({path, newBmp});
    return newBmp;
}

auto AlGame::Asset::getSample(const char* name) -> shared_ptr<ALLEGRO_SAMPLE> {
    if (Samples->contains(name)) return Samples->at(name);
    Slog->debug("Asset<Sound> Loading {}", name);

    auto smp = shared_ptr<ALLEGRO_SAMPLE>(al_load_sample((string(SamplePath) + name).c_str()),
                                          al_destroy_sample);
    if (smp == nullptr) throw Error("Asset<Sound> Failed to load " + string(name));
    Samples->insert({name, smp});
    return smp;
}
