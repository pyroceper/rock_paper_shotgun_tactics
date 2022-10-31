#include "unit.h"

Unit::Unit(int r, int c, int X, int Y, UnitType unit_type_)
{
    row = r;
    col = c;
    x = X;
    y = Y;
    movement_counter = 0;
    movement_radius = 3;//default
    is_moving = false;
    unit_type = unit_type_;
}

Unit::Unit()
{
    Unit(0, 0, 0, 0, NPC);
}

