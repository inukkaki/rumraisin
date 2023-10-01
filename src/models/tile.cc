#include "models/tile.h"

#include <array>

namespace {

std::array<Tile, kNumberOfTileIDs> tile_dict;

}  // namespace

const Tile& GetTile(unsigned int tile_id) {
    if (tile_id < kNumberOfTileIDs) {
        return tile_dict[tile_id];
    } else {
        return tile_dict[kUnknownTileID];
    }
}
