#include "models/tile.h"

#include <array>
#include <cassert>

namespace {

std::array<Tile, static_cast<int>(TileId::kMax)> tile_dict;

}  // namespace

void SetTileDict() {
    // just for debugging
    int index = static_cast<int>(TileId::kAir);
    tile_dict[index].id = TileId::kAir;
    tile_dict[index].is_close_t = false;
    tile_dict[index].is_close_l = false;
    tile_dict[index].is_close_r = false;
    tile_dict[index].is_close_d = false;
    tile_dict[index].debug_value = 100;

    index = static_cast<int>(TileId::kUnknown);
    tile_dict[index].id = TileId::kUnknown;
    tile_dict[index].is_close_t = false;
    tile_dict[index].is_close_l = false;
    tile_dict[index].is_close_r = false;
    tile_dict[index].is_close_d = false;
    tile_dict[index].debug_value = 101;

    index = static_cast<int>(TileId::kBlock);
    tile_dict[index].id = TileId::kBlock;
    tile_dict[index].is_close_t = true;
    tile_dict[index].is_close_l = true;
    tile_dict[index].is_close_r = true;
    tile_dict[index].is_close_d = true;
    tile_dict[index].debug_value = 102;
}

const Tile& GetTile(TileId tile_id) {
    int index = static_cast<int>(tile_id);
    assert((0 <= index) && (index < static_cast<int>(TileId::kMax)));
    return tile_dict[index];
}
