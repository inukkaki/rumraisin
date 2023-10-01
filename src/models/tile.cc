#include "models/tile.h"

#include <array>

namespace {

std::array<Tile, kNumberOfTileIDs> tile_dict;

}  // namespace

void SetTileDict() {
    // just for debugging
    tile_dict[0].debug_value = 100;
    tile_dict[1].debug_value = 101;
    tile_dict[2].debug_value = 102;
}

const Tile& GetTile(unsigned int tile_id) {
    if (tile_id < kNumberOfTileIDs) {
        return tile_dict[tile_id];
    } else {
        return tile_dict[kUnknownTileID];
    }
}
