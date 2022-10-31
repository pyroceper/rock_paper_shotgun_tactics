#include "turn_controller.h"

TurnController::TurnController()
{
    TurnController(1, 1, 1, 1);
}

TurnController::TurnController(int player_u, int npc_u, int total_player_u, int total_npc_u)
{
    player_units = player_u;
    npc_units = npc_u;
    total_player_units = total_player_u;
    total_npc_units = total_npc_u;
    is_player_turn = true;
}