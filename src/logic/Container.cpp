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

bool Container::getCellState(int x, int y) const {
	if (x < 0 || x >= width || y < 0 || y >= height) {
		return false;
	}
	return grid[x][y];
}

void Container::setCellState(int x, int y, bool state) {
	if (x >= 0 && x < width && y >= 0 && y < height) {
		grid[x][y] = state;
	}
}

void Container::resetContainer()
{
	for (auto& column : grid)
		std::fill(column.begin(), column.end(), false);
}

std::pair<int, int> Container::findMinMaxX() const {
    int min_x = 0, max_x = width;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (grid[x][y]) {
                min_x = std::min(min_x, x);
                max_x = std::max(max_x, x);
            }
        }
    }
    if (min_x - 1 >= 0 && max_x + 1 <= width)
    {
        return std::make_pair(min_x - 1, max_x + 2);
    }
    else
    {
        return std::make_pair(0, width + 1);
    }
}

std::pair<int, int> Container::findMinMaxY() const {
    int min_y = 0, max_y = height;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (grid[x][y]) {
                min_y = std::min(min_y, y);
                max_y = std::max(max_y, y);
            }
        }
    }

    if (min_y - 1 >= 0 && max_y + 1 <= height)
    {
        return std::make_pair(min_y - 1, max_y + 2);
    }
    else
    {
        return std::make_pair(0, height + 1);
    }
}