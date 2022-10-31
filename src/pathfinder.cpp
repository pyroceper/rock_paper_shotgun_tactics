#include "pathfinder.h"

Pathfinder::Pathfinder()
{
    reset();
}

void Pathfinder::reset()
{
    found = false;
    for(int i=0;i<ROW*COL;i++)
    {
        visited[i] = false;
    }
    for(int i=0;i<ROW;i++)
    {
        for(int j=0;j<COL;j++)
        {
            game[i][j] = -1;
        }
    }
    queue_r.clear();
    queue_c.clear();
    queue_count.clear();
}

bool Pathfinder::is_valid(int row, int col)
{
    return ((row >= 0 && row < ROW) && (col >= 0 && col < COL));
}

void Pathfinder::add_obstacle(int row, int col)
{
    obstacles[ROW* row + col] = true;
}

bool Pathfinder::check_obstacle(int row, int col)
{
    return obstacles[ROW * row + col];
}

void Pathfinder::search(int row, int col)
{   
    reset();
    int count = 1;
    queue_r.push(row); queue_c.push(col);
    queue_count.push(count);
    visited[ROW * row + col] = true;

    while(!queue_r.empty())
    {
        int rr = queue_r.front(); queue_r.pop();
        int cc = queue_c.front(); queue_c.pop();
        
        count = queue_count.front(); queue_count.pop();
        game[rr][cc] = count;

        //SOUTH
        if(is_valid(rr+1, cc) && !visited[ROW * (rr+1) + cc] && !obstacles[ROW * (rr+1) + cc])
        {
            queue_r.push(rr+1); queue_c.push(cc); queue_count.push(count + 1);
            visited[ROW * (rr+1) + cc] = true;
        }
        //NORTH
        if(is_valid(rr-1, cc) && !visited[ROW * (rr-1) + cc] && !obstacles[ROW * (rr-1) + cc])
        {
            queue_r.push(rr-1); queue_c.push(cc); queue_count.push(count + 1);
            visited[ROW * (rr-1) + cc] = true;
        }
        //EAST
        if(is_valid(rr, cc+1) && !visited[ROW * rr + (cc+1)] && !obstacles[ROW * rr + (cc+1)])
        {
            queue_r.push(rr); queue_c.push(cc+1); queue_count.push(count + 1);
            visited[ROW * rr + (cc+1)] = true;
        }
        //WEST
        if(is_valid(rr, cc-1) && !visited[ROW * rr + (cc-1)] && !obstacles[ROW * rr + (cc-1)])
        {
            queue_r.push(rr); queue_c.push(cc-1); queue_count.push(count + 1);
            visited[ROW * rr + (cc-1)] = true;
        }
    }
}