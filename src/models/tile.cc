#include "models/tile.h"

#include <array>

namespace {

std::array<Tile, kNumberOfTileIds> tile_dict;

}  // namespace

void SetTileDict() {
    // just for debugging
    tile_dict[0].coll_id = TileCollisionId::kNone;
    tile_dict[1].coll_id = TileCollisionId::kNone;
    tile_dict[2].coll_id = TileCollisionId::kSolid;
    tile_dict[0].debug_value = 100;
    tile_dict[1].debug_value = 101;
    tile_dict[2].debug_value = 102;
}

const Tile& GetTile(unsigned int tile_id) {
    if (tile_id < kNumberOfTileIds) {
        return tile_dict[tile_id];
    } else {
        return tile_dict[kUnknownTileId];
    }
}
