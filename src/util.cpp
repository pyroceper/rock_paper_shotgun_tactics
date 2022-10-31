#include "util.h"

void Util::move_unit(Unit &curr_unit, bn::sprite_ptr& curr_sprite, Pathfinder& pf, int& movement_counter)
{
    if(movement_counter == 30 && curr_unit.movement_counter > 0)
    {
        // BN_LOG("moving");

        if(pf.is_valid(curr_unit.row + 1, curr_unit.col) && pf.game[curr_unit.row + 1][curr_unit.col] == pf.game[curr_unit.row][curr_unit.col] - 1)
        {
            BN_LOG("SOUTH");

            curr_unit.row = curr_unit.row + 1;
            curr_unit.y = curr_unit.y + 16;
            curr_sprite.set_y(curr_unit.y);
            curr_unit.movement_counter--;
        }
        else if(pf.is_valid(curr_unit.row, curr_unit.col + 1) && pf.game[curr_unit.row][curr_unit.col + 1] == pf.game[curr_unit.row][curr_unit.col] - 1)
        {
            BN_LOG("EAST");

            curr_unit.col = curr_unit.col + 1;
            curr_unit.x = curr_unit.x + 16;
            curr_sprite.set_x(curr_unit.x);
            curr_sprite.set_horizontal_flip(false);
            curr_unit.movement_counter--;
        }
        else if(pf.is_valid(curr_unit.row - 1, curr_unit.col) && pf.game[curr_unit.row - 1][curr_unit.col] == pf.game[curr_unit.row][curr_unit.col] - 1)
        {
            BN_LOG("NORTH");

            curr_unit.row = curr_unit.row - 1;
            curr_unit.y = curr_unit.y - 16;
            curr_sprite.set_y(curr_unit.y);
            curr_unit.movement_counter--;
        }
        else if(pf.is_valid(curr_unit.row, curr_unit.col - 1) && pf.game[curr_unit.row][curr_unit.col - 1] == pf.game[curr_unit.row][curr_unit.col] - 1)
        {
            BN_LOG("WEST");

            curr_unit.col = curr_unit.col - 1;
            curr_unit.x = curr_unit.x - 16;
            curr_sprite.set_x(curr_unit.x);
            curr_sprite.set_horizontal_flip(true);
            curr_unit.movement_counter--;
        }
       
        movement_counter = 0;

    }
    movement_counter++;
        //     if(!tc.is_player_turn)
        // {
        //     tc.turn_timer--;
        // }
}

void Util::vaild_moves(Pathfinder& pf, int row, int col, int count)
{
    if(!pf.is_valid(row, col) || count == 0 || pf.game[row][col] != -1)
        return;
        
    pf.game[row][col] = count;
    
    vaild_moves(pf, row - 1, col, count - 1); //SOUTH
    vaild_moves(pf, row + 1, col, count - 1); // NORTH
    vaild_moves(pf, row, col - 1, count - 1); // WEST
    vaild_moves(pf, row, col + 1, count - 1); // EAST
}

void Util::hide_tiles(bn::sprite_ptr& v_tile_1, bn::sprite_ptr& v_tile_2,
        bn::sprite_ptr& v_tile_3, bn::sprite_ptr& v_tile_4, bn::sprite_ptr& v_tile_5, bn::sprite_ptr& v_tile_6,
        bn::sprite_ptr& v_tile_7, bn::sprite_ptr& v_tile_8, bn::sprite_ptr& v_tile_9, bn::sprite_ptr& v_tile_10,
        bn::sprite_ptr& v_tile_11, bn::sprite_ptr& v_tile_12)
{
    v_tile_1.set_visible(false);
    v_tile_2.set_visible(false);
    v_tile_3.set_visible(false);
    v_tile_4.set_visible(false);

    v_tile_5.set_visible(false);
    v_tile_6.set_visible(false);
    v_tile_7.set_visible(false);
    v_tile_8.set_visible(false);

    v_tile_9.set_visible(false);
    v_tile_10.set_visible(false);
    v_tile_11.set_visible(false);
    v_tile_12.set_visible(false);
}

void Util::paint_moves_1(Unit& curr_unit,Pathfinder& pf, bn::sprite_ptr& v_tile_1, bn::sprite_ptr& v_tile_2,
        bn::sprite_ptr& v_tile_3, bn::sprite_ptr& v_tile_4)
{
    int origin_pos_x = -104; int origin_pos_y = -73;//temp
    if(pf.game[curr_unit.row + 1][curr_unit.col] == 2)
    {
        v_tile_1.set_position(origin_pos_x + (curr_unit.col * 16) , origin_pos_y + ((curr_unit.row + 1) * 16));
        v_tile_1.set_visible(true);
    }
    if(pf.game[curr_unit.row - 1][curr_unit.col] == 2)
    {
        v_tile_2.set_position(origin_pos_x + (curr_unit.col * 16) , origin_pos_y + ((curr_unit.row - 1) * 16));
        v_tile_2.set_visible(true);
    }
    if(pf.game[curr_unit.row][curr_unit.col + 1] == 2)
    {
        v_tile_3.set_position(origin_pos_x + ((curr_unit.col + 1) * 16) , origin_pos_y + (curr_unit.row * 16));
        v_tile_3.set_visible(true);
    }
    if(pf.game[curr_unit.row][curr_unit.col - 1] == 2)
    {
        v_tile_4.set_position(origin_pos_x + ((curr_unit.col - 1) * 16) , origin_pos_y + (curr_unit.row * 16));
        v_tile_4.set_visible(true);
    }
}

void Util::paint_moves_2(Unit& curr_unit,Pathfinder& pf, bn::sprite_ptr& v_tile_5, bn::sprite_ptr& v_tile_6,
        bn::sprite_ptr& v_tile_7, bn::sprite_ptr& v_tile_8)
{
    int origin_pos_x = -104; int origin_pos_y = -73;//temp
    if(pf.game[curr_unit.row + 2][curr_unit.col] == 1)
    {
        v_tile_5.set_position(origin_pos_x + (curr_unit.col * 16) , origin_pos_y + ((curr_unit.row + 2) * 16));
        v_tile_5.set_visible(true);
    }
    if(pf.game[curr_unit.row - 2][curr_unit.col] == 1)
    {
        v_tile_6.set_position(origin_pos_x + (curr_unit.col * 16) , origin_pos_y + ((curr_unit.row - 2) * 16));
        v_tile_6.set_visible(true);
    }
    if(pf.game[curr_unit.row][curr_unit.col + 2] == 1)
    {
        v_tile_7.set_position(origin_pos_x + ((curr_unit.col + 2) * 16) , origin_pos_y + (curr_unit.row * 16));
        v_tile_7.set_visible(true);
    }
    if(pf.game[curr_unit.row][curr_unit.col - 2] == 1)
    {
        v_tile_8.set_position(origin_pos_x + ((curr_unit.col - 2) * 16) , origin_pos_y + (curr_unit.row * 16));
        v_tile_8.set_visible(true);
    }
}

void Util::paint_moves_3(Unit& curr_unit,Pathfinder& pf, bn::sprite_ptr& v_tile_9, bn::sprite_ptr& v_tile_10,
        bn::sprite_ptr& v_tile_11, bn::sprite_ptr& v_tile_12)
{
    int origin_pos_x = -104; int origin_pos_y = -73;//temp
    if(pf.game[curr_unit.row - 1][curr_unit.col - 1] == 1)
    {
        v_tile_9.set_position(origin_pos_x + ((curr_unit.col -1) * 16) , origin_pos_y + ((curr_unit.row - 1) * 16));
        v_tile_9.set_visible(true);
    }
    if(pf.game[curr_unit.row - 1][curr_unit.col + 1] == 1)
    {
        v_tile_10.set_position(origin_pos_x + ((curr_unit.col + 1) * 16) , origin_pos_y + ((curr_unit.row - 1) * 16));
        v_tile_10.set_visible(true);
    }
    if(pf.game[curr_unit.row + 1][curr_unit.col - 1] == 1)
    {
        v_tile_11.set_position(origin_pos_x + ((curr_unit.col - 1) * 16) , origin_pos_y + ((curr_unit.row + 1) * 16));
        v_tile_11.set_visible(true);
    }
    if(pf.game[curr_unit.row + 1][curr_unit.col + 1] == 1)
    {
        v_tile_12.set_position(origin_pos_x + ((curr_unit.col + 1) * 16) , origin_pos_y + ((curr_unit.row + 1) * 16));
        v_tile_12.set_visible(true);
    }
}
