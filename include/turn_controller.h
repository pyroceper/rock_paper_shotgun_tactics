#ifndef TURN_CONTROLLER_H
#define TURN_CONTROLLER_H

class TurnController
{
    public:
        TurnController();
        TurnController(int player_u, int npc_u, int total_player_u, int total_npc_u);
        bool is_player_turn = false;
        int turn_timer = 20;
    private:
        int player_units;
        int npc_units;
        int total_player_units;
        int total_npc_units;
};


#endif