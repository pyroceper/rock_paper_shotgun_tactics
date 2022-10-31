#ifndef TILES_H
#define TILES_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_items_tiles.h"

struct Tile
{
    bn::sprite_ptr tile = bn::sprite_items::tiles.create_sprite(0, 0);
};

#endif