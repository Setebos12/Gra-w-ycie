#include "PointHandle.h"

PointHandle::PointHandle(const Container& container) 
	: container(container) {}

bool PointHandle::shouldCellLive(int x, int y) const
{
    int liveNeighbors = countLiveNeighbors(x, y);
    bool isAlive = container.getCellState(x, y);

    // Conway's Game of Life rules:
    // 1. Any live cell with 2 or 3 neighbors survives.
    // 2. Any dead cell with exactly 3 neighbors becomes alive.
    // 3. All other cells die or stay dead.
    return (isAlive && (liveNeighbors == 2 || liveNeighbors == 3)) ||
        (!isAlive && liveNeighbors == 3);
}

int PointHandle::countLiveNeighbors(int x, int y) const
{
	int count = 0;
	const int width = container.getWidth();
	const int height = container.getHeight();
	
    // we check all cell in 3x3 square around
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            if (dx == 0 && dy == 0) continue;   // we pass the middle (cell that is being checked)

            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < width && ny >= 0 && ny < height)
            {
                if (container.getCellState(nx, ny))
                {
                    count++;
                }
            }
        }
    }
    return count;
}
