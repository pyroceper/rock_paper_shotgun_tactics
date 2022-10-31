#include "bn_core.h"
#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_blending.h"
#include "bn_bg_palettes.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprites_mosaic.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_builder.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_first_attributes.h"
#include "bn_sprite_third_attributes.h"
#include "bn_sprite_position_hbe_ptr.h"
#include "bn_sprite_first_attributes_hbe_ptr.h"
#include "bn_sprite_third_attributes_hbe_ptr.h"
#include "bn_sprite_affine_second_attributes.h"
#include "bn_sprite_regular_second_attributes.h"
#include "bn_sprite_affine_second_attributes_hbe_ptr.h"
#include "bn_sprite_regular_second_attributes_hbe_ptr.h"
#include "bn_log.h"

#include "bn_sprite_items_tiles.h"
#include "bn_sprite_items_assault_class_.h"
#include "bn_sprite_items_selection_cursor.h"
#include "bn_sprite_items_dst_cursor.h"
#include "bn_sprite_items_g_arrow.h"
#include "bn_sprite_items_wasp.h"
#include "bn_regular_bg_items_board.h"

#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"

#include "scene.h"
#include "util.h"
#include "unit.h"
#include "tiles.h"
#include "queue.h"
#include "pathfinder.h"
#include "turn_controller.h"


int main()
{
    bn::core::init();

    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    text_generator.set_alignment(bn::sprite_text_generator::alignment_type::LEFT);
   
    bn::vector<bn::sprite_ptr, 32> text_sprites;
 
    bn::bg_palettes::set_transparent_color(bn::color(16, 16, 16));

    bn::string_view debug_text[2];
    debug_text[0] = "Player turn";
    text_generator.generate(45, 70, debug_text[0], text_sprites);

    bn::regular_bg_ptr board_bg = bn::regular_bg_items::board.create_bg(0, 0);

    int movement_counter = 0;
    const int origin_r = 0;
    const int origin_c = 0;
    const int origin_pos_x = -104;
    const int origin_pos_y = -73;

    int wasp_r = 5;
    int wasp_c = 8;
    int wasp_pos_x = origin_pos_x + (16 * wasp_c);
    int wasp_pos_y = origin_pos_y + (16 * wasp_r);

    bn::sprite_ptr red_tile = bn::sprite_items::dst_cursor.create_sprite(origin_pos_x, origin_pos_y, 1);

    bn::sprite_ptr sp_2 = bn::sprite_items::assault_class_.create_sprite(origin_pos_x, origin_pos_y);

    bn::sprite_ptr sp_wasp = bn::sprite_items::wasp.create_sprite(wasp_pos_x, wasp_pos_y);

    bn::sprite_animate_action<8> sp_wasp_animate_action = bn::create_sprite_animate_action_forever(
        sp_wasp, 12, bn::sprite_items::wasp.tiles_item(), 0, 1, 2, 3, 4, 5, 6, 7);

    bn::sprite_animate_action<4> sp_2_animate_action = bn::create_sprite_animate_action_forever(
        sp_2, 12, bn::sprite_items::assault_class_.tiles_item(), 0, 1, 2, 3);

    Unit player_unit(origin_r, origin_c, origin_pos_x, origin_pos_y, UnitType::Player);
    player_unit.movement_counter = 100; //debug
    Unit *curr_unit = &player_unit;

    Unit wasp_unit(wasp_r, wasp_c, wasp_pos_x, wasp_pos_y, UnitType::NPC);
    wasp_unit.movement_counter = 3;

    bn::sprite_ptr curr_sp = sp_2;


    bn::sprite_ptr v_tile_1 = bn::sprite_items::dst_cursor.create_sprite(origin_pos_x, origin_pos_y, 2);
    bn::sprite_ptr v_tile_2 = bn::sprite_items::dst_cursor.create_sprite(origin_pos_x, origin_pos_y, 2);
    bn::sprite_ptr v_tile_3 = bn::sprite_items::dst_cursor.create_sprite(origin_pos_x, origin_pos_y, 2);
    bn::sprite_ptr v_tile_4 = bn::sprite_items::dst_cursor.create_sprite(origin_pos_x, origin_pos_y, 2);
    v_tile_1.set_visible(false);
    v_tile_2.set_visible(false);
    v_tile_3.set_visible(false);
    v_tile_4.set_visible(false);

    bn::sprite_ptr v_tile_5 = bn::sprite_items::dst_cursor.create_sprite(origin_pos_x, origin_pos_y, 2);
    bn::sprite_ptr v_tile_6 = bn::sprite_items::dst_cursor.create_sprite(origin_pos_x, origin_pos_y, 2);
    bn::sprite_ptr v_tile_7 = bn::sprite_items::dst_cursor.create_sprite(origin_pos_x, origin_pos_y, 2);
    bn::sprite_ptr v_tile_8 = bn::sprite_items::dst_cursor.create_sprite(origin_pos_x, origin_pos_y, 2);

    v_tile_5.set_visible(false);
    v_tile_6.set_visible(false);
    v_tile_7.set_visible(false);
    v_tile_8.set_visible(false);

    bn::sprite_ptr v_tile_9 = bn::sprite_items::dst_cursor.create_sprite(origin_pos_x, origin_pos_y, 2);
    bn::sprite_ptr v_tile_10 = bn::sprite_items::dst_cursor.create_sprite(origin_pos_x, origin_pos_y, 2);
    bn::sprite_ptr v_tile_11 = bn::sprite_items::dst_cursor.create_sprite(origin_pos_x, origin_pos_y, 2);
    bn::sprite_ptr v_tile_12 = bn::sprite_items::dst_cursor.create_sprite(origin_pos_x, origin_pos_y, 2);

    v_tile_9.set_visible(false);
    v_tile_10.set_visible(false);
    v_tile_11.set_visible(false);
    v_tile_12.set_visible(false);

    int cursor_pos_x = origin_pos_x;
    int cursor_pos_y = origin_pos_y;
    int cursor_r = 0;
    int cursor_c = 0;
    bn::sprite_ptr sp_cursor = bn::sprite_items::selection_cursor.create_sprite(cursor_pos_x, cursor_pos_y);
    bn::sprite_ptr sp_cursor_blocked = bn::sprite_items::selection_cursor.create_sprite(cursor_pos_x, cursor_pos_y, 2);
    sp_cursor_blocked.set_visible(false);

    //UI
    int sp_arrow_x = 45; int sp_arrow_y = -20;
    bn::sprite_ptr sp_arrow = bn::sprite_items::g_arrow.create_sprite(sp_arrow_x, sp_arrow_y);
    sp_arrow.set_visible(false);
    bn::sprite_text_generator ui_text_generator(common::variable_8x16_sprite_font);
    ui_text_generator.set_alignment(bn::sprite_text_generator::alignment_type::LEFT);

    bn::vector<bn::sprite_ptr, 12> ui_text_1_sp;
    bn::vector<bn::sprite_ptr, 12> ui_text_2_sp;
    bn::vector<bn::sprite_ptr, 12> ui_text_3_sp;
    bn::vector<bn::sprite_ptr, 12> ui_text_4_sp;
    bn::string_view ui_text[4];

    bn::bg_palettes::set_transparent_color(bn::color(16, 16, 16));

    ui_text[0] = "Move";
    ui_text[1] = "Attack";
    ui_text[2] = "End Turn";
    ui_text[3] = "Back";


    Pathfinder pf;

    int dst_r = -1;
    int dst_c = -1;

    
    red_tile.set_position(origin_pos_x + (dst_r * 16) , origin_pos_y + ((dst_c - 1) * 16));

    pf.add_obstacle(0, 4);
    pf.add_obstacle(1, 1);
    pf.add_obstacle(2, 1);
    pf.add_obstacle(6, 5);
    pf.add_obstacle(8, 5);
    pf.add_obstacle(8, 6);
    pf.add_obstacle(8, 7);
    pf.add_obstacle(8, 8);


    TurnController tc;
    tc.is_player_turn = true;

    bool is_menu = false;
    bool prepare_menu = false;

    while(true)
    {
        bn::core::update();
        //keypad controls
        if(!is_menu)
        {
            if(bn::keypad::pressed(bn::keypad::key_type::LEFT) && pf.is_valid(cursor_r, cursor_c - 1) && !pf.check_obstacle(cursor_r, cursor_c - 1))
            {
                cursor_pos_x -= 16;
                cursor_c--;
            }
            else if(bn::keypad::pressed(bn::keypad::key_type::RIGHT) && pf.is_valid(cursor_r, cursor_c + 1) && !pf.check_obstacle(cursor_r, cursor_c + 1))
            {
                cursor_pos_x += 16;
                cursor_c++;
            }
            else if(bn::keypad::pressed(bn::keypad::key_type::DOWN) && pf.is_valid(cursor_r + 1, cursor_c) && !pf.check_obstacle(cursor_r + 1, cursor_c))
            {
                cursor_pos_y += 16;
                cursor_r++;
            }
            else if(bn::keypad::pressed(bn::keypad::key_type::UP) && pf.is_valid(cursor_r - 1, cursor_c) && !pf.check_obstacle(cursor_r - 1, cursor_c))
            {
                cursor_pos_y -= 16;
                cursor_r--;
            }
        }
        else
        {
            if(bn::keypad::pressed(bn::keypad::key_type::DOWN))
            {
                sp_arrow_y += 20;
                if(sp_arrow_y >= 40)
                    sp_arrow_y = 40;
            }
            else if(bn::keypad::pressed(bn::keypad::key_type::UP))
            {
                sp_arrow_y -= 20;
                if(sp_arrow_y <= -20)
                    sp_arrow_y = -20;
            }
        }
        
        if(bn::keypad::pressed(bn::keypad::key_type::B) && is_menu)
        {
            sp_arrow.set_visible(false);
            is_menu = false;
        }

        if(prepare_menu)
        {
            ui_text_1_sp.clear();
            ui_text_2_sp.clear();
            ui_text_3_sp.clear();
            ui_text_4_sp.clear();
            ui_text_generator.generate(60, -20, ui_text[0], ui_text_1_sp); 
            ui_text_generator.generate(60, 0, ui_text[1], ui_text_2_sp);
            ui_text_generator.generate(60, 20, ui_text[2], ui_text_3_sp);
            ui_text_generator.generate(60, 40, ui_text[3], ui_text_4_sp);
            prepare_menu = false;
        }

        if(!is_menu && !prepare_menu)
        {
            ui_text_1_sp.clear();
            ui_text_2_sp.clear();
            ui_text_3_sp.clear();
            ui_text_4_sp.clear();

            Util::hide_tiles(v_tile_1, v_tile_2, v_tile_3, v_tile_4, v_tile_5, v_tile_6, v_tile_7, v_tile_8, v_tile_9, v_tile_10, v_tile_11, v_tile_12);
        }

        if(bn::keypad::pressed(bn::keypad::key_type::A) && tc.is_player_turn && !is_menu)
        {
            //if cursor on unit
            //then show available path
            //else
            if(cursor_r == curr_unit->row && cursor_c == curr_unit->col)
            {

                sp_arrow.set_visible(true);
                is_menu = true;
                prepare_menu = true;

                //get movement radius
                BN_LOG("Movement radius");
                Util::vaild_moves(pf, curr_unit->row, curr_unit->col, curr_unit->movement_radius);
                Util::paint_moves_1(*curr_unit, pf, v_tile_1, v_tile_2, v_tile_3, v_tile_4);
                Util::paint_moves_2(*curr_unit, pf, v_tile_5, v_tile_6, v_tile_7, v_tile_8);
                Util::paint_moves_3(*curr_unit, pf, v_tile_9, v_tile_10, v_tile_11, v_tile_12);
                pf.reset();
            }
            else
            {
                Util::hide_tiles(v_tile_1, v_tile_2, v_tile_3, v_tile_4, v_tile_5, v_tile_6, v_tile_7, v_tile_8, v_tile_9, v_tile_10, v_tile_11, v_tile_12);

                    sp_arrow.set_visible(false);

                    dst_r = cursor_r;
                    dst_c = cursor_c;
                    BN_LOG(dst_r, " , ", dst_c);
                    BN_LOG(curr_unit->row, " , ", curr_unit->col);
                    pf.search(dst_r, dst_c);
                    for(int i =0;i<ROW;i++)
                    {
                        for(int j=0;j<COL;j++)
                        {
                            BN_LOG(pf.game[i][j]);
                        }
                        BN_LOG("----");
                    }
                    red_tile.set_position(origin_pos_x + (dst_c * 16) , origin_pos_y + (dst_r * 16));
  
            }
        }
        if((curr_unit->row != dst_r || curr_unit->col != dst_c))
        {

            Util::move_unit(*curr_unit, curr_sp, pf, movement_counter);
        }
        else if((curr_unit->row == dst_r) && (curr_unit->col == dst_c))
        {
            if(tc.is_player_turn)
            {
                dst_r = dst_c = -1;
                red_tile.set_position(origin_pos_x + (dst_c * 16) , origin_pos_y + (dst_r * 16)); // hide tile
                BN_LOG("CPU turn");
                debug_text[0] = "CPU turn";
                text_sprites.clear();
                text_generator.generate(45, 70, debug_text[0], text_sprites);
                sp_cursor_blocked.set_visible(true);
                sp_cursor.set_visible(false);
                pf.reset();
                //after player's turn
                //transfer control to CPU
                tc.is_player_turn = false;
                tc.turn_timer = 100;
                dst_r = player_unit.row;
                dst_c = player_unit.col;
                curr_unit = &wasp_unit;
                wasp_unit.movement_counter = 3;
                curr_sp = sp_wasp;
                BN_LOG(dst_r, " , ", dst_c);
                BN_LOG(curr_unit->row, " , ", curr_unit->col);
                pf.search(dst_r, dst_c);
            }
            else 
            {
                BN_LOG("player turn");
                debug_text[0] = "Player turn";
                text_sprites.clear();
                text_generator.generate(45, 70, debug_text[0], text_sprites);
                sp_cursor.set_visible(true);
                sp_cursor_blocked.set_visible(false);
                dst_r = dst_c = -1;
                pf.reset();
                tc.is_player_turn = true;
                curr_unit = &player_unit;
                player_unit.movement_counter = 100; //debug
                curr_sp = sp_2;
            }
        }
        
        if(curr_unit->movement_counter == 0 || (!tc.is_player_turn  && tc.turn_timer <= 0))
        {
                BN_LOG("player turn");
                debug_text[0] = "Player turn";
                text_sprites.clear();
                text_generator.generate(45, 70, debug_text[0], text_sprites);
                sp_cursor.set_visible(true);
                sp_cursor_blocked.set_visible(false);
                dst_r = dst_c = -1;
                pf.reset();
                tc.is_player_turn = true;
                curr_unit = &player_unit;
                player_unit.movement_counter = 100; //debug
                curr_sp = sp_2;           
        }

        sp_2_animate_action.update();
        sp_wasp_animate_action.update();
        sp_cursor.set_position(cursor_pos_x, cursor_pos_y);
        sp_cursor_blocked.set_position(cursor_pos_x, cursor_pos_y);
        sp_arrow.set_position(sp_arrow_x, sp_arrow_y);
    }
    return 0;
}
