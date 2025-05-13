#pragma once

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
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			setCellState(x, y, 0);
		}
	}
}