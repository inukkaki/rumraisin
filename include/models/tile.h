#ifndef RUMRAISIN_MODELS_TILE_H_
#define RUMRAISIN_MODELS_TILE_H_

inline constexpr int kNumberOfTileIDs = 3;

inline constexpr int kUnknownTileID = 1;

struct Tile {
    // just for debugging
    int debug_value;
};

void SetTileDict();

const Tile& GetTile(unsigned int tile_id);

#endif  // RUMRAISIN_MODELS_TILE_H_
