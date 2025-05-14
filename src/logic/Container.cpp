#include "Container.h"

Container::Container(int width, int height)
	: width(width), height(height)
{
	grid.resize(width);
	for (auto& column : grid)
	{
		column.resize(height, false);  // all cells are not alive
	}
}

int Container::getWidth() const
{
	return width;
}

int Container::getHeight() const
{
	return height;
}

bool Container::getCellState(int x, int y) const
{
	return grid[x][y];
}

void Container::setCellState(int x, int y, bool state)
{
	grid[x][y] = state;
}

void Container::resetContainer()
{
	for (auto& column : grid)
		std::fill(column.begin(), column.end(), false);
}
