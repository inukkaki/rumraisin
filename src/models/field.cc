#include "models/field.h"

#include "models/tile.h"

void Field::Load() {
    // just for debugging
    for (int i = 0; i < kFieldMaxHeight; ++i) {
        for (int j = 0; j < kFieldMaxWidth; ++j) {
            collision_[i][j] = 0;
        }
    }
}

const Tile& Field::GetCollision(int row, int col) const {
    unsigned int tile_id = kUnknownTileId;
    if ((0 <= row) && (row < kFieldMaxHeight)) {
        if ((0 <= col) && (col < kFieldMaxWidth)) {
            tile_id = collision_[row][col];
        }
    }
    return GetTile(tile_id);
}
