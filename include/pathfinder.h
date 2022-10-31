#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "queue.h"
#include "stack.h"
#include "bn_log.h"

#define ROW 9
#define COL 9

class Pathfinder
{
    public:
        Pathfinder();
        void reset();
        bool is_valid(int row, int col);
        bool found;
        int game[ROW][COL] = {0};
        void search(int row, int col);
        void add_obstacle(int row, int col);
        bool check_obstacle(int row, int col);
    private:
        Queue<int> queue_r {};
        Queue<int> queue_c {};
        Queue<int> queue_count {};
        bool visited[ROW*COL] = {false};
        bool obstacles[ROW*COL] = {false};
};

#endif