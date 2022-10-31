#ifndef UNIT_H
#define UNIT_H

enum UnitType { Player, NPC};

class Unit
{
    public:
        Unit(int r, int c, int X, int Y, UnitType unit_type_);
        Unit();

        int row;
        int col;

        int x;
        int y;

        int movement_counter;
        int movement_radius;
        bool is_moving;

        UnitType unit_type;
};


#endif