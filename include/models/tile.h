#ifndef RUMRAISIN_MODELS_TILE_H_
#define RUMRAISIN_MODELS_TILE_H_

enum class TileId : unsigned char {
    kAir,
    kUnknown,
    kBlock,
    kMax
};

struct Tile {
    TileId id;

    bool is_close_t;  // On the top-side
    bool is_close_l;  // On the left side
    bool is_close_r;  // On the right side
    bool is_close_d;  // On the down-side

    // just for debugging
    int debug_value;
};

void SetTileDict();

const Tile& GetTile(TileId tile_id);

#endif  // RUMRAISIN_MODELS_TILE_H_
