#ifndef UTIL_H
#define UTIL_H

#include "bn_sprite_ptr.h"

#include "unit.h"
#include "pathfinder.h"
#include "turn_controller.h"

namespace Util
{
    void move_unit(Unit& curr_unit, bn::sprite_ptr& curr_sprite, Pathfinder& pf, int& movement_counter);
    void vaild_moves(Pathfinder& pf, int row, int col, int count);
    void paint_moves_1(Unit& curr_unit,Pathfinder& pf, bn::sprite_ptr& v_tile_1, bn::sprite_ptr& v_tile_2,
        bn::sprite_ptr& v_tile_3, bn::sprite_ptr& v_tile_4);
    void paint_moves_2(Unit& curr_unit,Pathfinder& pf, bn::sprite_ptr& v_tile_5, bn::sprite_ptr& v_tile_6,
        bn::sprite_ptr& v_tile_7, bn::sprite_ptr& v_tile_8);
    void paint_moves_3(Unit& curr_unit,Pathfinder& pf, bn::sprite_ptr& v_tile_9, bn::sprite_ptr& v_tile_10,
        bn::sprite_ptr& v_tile_11, bn::sprite_ptr& v_tile_12);
    void hide_tiles(bn::sprite_ptr& v_tile_1, bn::sprite_ptr& v_tile_2,
        bn::sprite_ptr& v_tile_3, bn::sprite_ptr& v_tile_4, bn::sprite_ptr& v_tile_5, bn::sprite_ptr& v_tile_6,
        bn::sprite_ptr& v_tile_7, bn::sprite_ptr& v_tile_8, bn::sprite_ptr& v_tile_9, bn::sprite_ptr& v_tile_10,
        bn::sprite_ptr& v_tile_11, bn::sprite_ptr& v_tile_12);
};

#endif