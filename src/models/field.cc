#include "models/field.h"

#include "models/tile.h"

void Field::Load() {
    // just for debugging
    for (int i = 0; i < kFieldMaxHeight; ++i) {
        for (int j = 0; j < kFieldMaxWidth; ++j) {
            collision_[i][j] = 0;
        }
    }
    collision_[0][0] = 1;
    collision_[0][kFieldMaxWidth - 1] = 1;
    collision_[kFieldMaxHeight - 1][kFieldMaxWidth - 1] = 1;
    for (int i = kFieldMaxHeight - 5; i < kFieldMaxHeight - 2; ++i) {
        for (int j = 0; j < kFieldMaxWidth - 2; ++j) {
            collision_[i][j] = 2;
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
