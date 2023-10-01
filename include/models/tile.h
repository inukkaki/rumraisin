#ifndef RUMRAISIN_MODELS_TILE_H_
#define RUMRAISIN_MODELS_TILE_H_

inline constexpr int kNumberOfTileIDs = 3;

inline constexpr int kUnknownTileID = 1;

struct Tile {
    //
};

const Tile& GetTile(unsigned int tile_id);

#endif  // RUMRAISIN_MODELS_TILE_H_
