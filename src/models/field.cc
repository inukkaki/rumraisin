#include "models/field.h"

#include <array>

#include "models/tile.h"

namespace {

std::array<
    std::array<int, kFieldMaxWidth>,
    kFieldMaxHeight> field_reference_count;

}  // namespace

void InitFieldReferenceCount() {
    for (int i = 0; i < kFieldMaxHeight; ++i) {
        for (int j = 0; j < kFieldMaxWidth; ++j) {
            field_reference_count[i][j] = 0;
        }
    }
}

namespace {

void IncrementFieldReferenceCount(int row, int col) {
    bool cond_row = (0 <= row) && (row < kFieldMaxHeight);
    bool cond_col = (0 <= col) && (col < kFieldMaxWidth);
    if (cond_row && cond_col) {
        ++field_reference_count[row][col];
    }
}

}  // namespace

void Field::Load() {
    // just for debugging
    for (int i = 0; i < kFieldMaxHeight; ++i) {
        for (int j = 0; j < kFieldMaxWidth; ++j) {
            collision_[i][j] = TileId::kAir;
        }
    }
    collision_[0][0] = TileId::kUnknown;
    collision_[0][kFieldMaxWidth - 1] = TileId::kUnknown;
    collision_[kFieldMaxHeight - 1][kFieldMaxWidth - 1] = TileId::kUnknown;
    for (int i = kFieldMaxHeight - 5; i < kFieldMaxHeight - 2; ++i) {
        for (int j = 0; j < kFieldMaxWidth - 2; ++j) {
            collision_[i][j] = TileId::kBlock;
        }
    }
}

const Tile& Field::GetCollision(int row, int col) const {
    TileId tile_id = TileId::kUnknown;
    bool cond_row = (0 <= row) && (row < kFieldMaxHeight);
    bool cond_col = (0 <= col) && (col < kFieldMaxWidth);
    if (cond_row && cond_col) {
        tile_id = collision_[row][col];

        // just for debugging
        IncrementFieldReferenceCount(row, col);
    }
    return GetTile(tile_id);
}
