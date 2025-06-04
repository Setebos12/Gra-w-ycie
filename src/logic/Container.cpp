#include "container.h"

Container::Container(int width, int height)
	: width_(width), height_(height)
{
	grid_.resize(width);
	for (auto& column : grid_)
	{
		column.resize(height, false);  // all cells are not alive
	}
}

int Container::getWidth() const
{
	return width_;
}

int Container::getHeight() const
{
	return height_;
}

bool Container::getCellState(int x, int y) const {
	if (x < 0 || x >= width_ || y < 0 || y >= height_) {
		return false;
	}
	return grid_[x][y];
}

void Container::setCellState(int x, int y, bool state) {
	if (x >= 0 && x < width_ && y >= 0 && y < height_) {
		grid_[x][y] = state;
	}
}

void Container::resetContainer()
{
	for (auto& column : grid_)
		std::fill(column.begin(), column.end(), false);
}

std::pair<int, int> Container::findMinMaxX() const {
    int min_x = 0, max_x = width_;

    for (int x = 0; x < width_; ++x) {
        for (int y = 0; y < height_; ++y) {
            if (grid_[x][y]) {
                min_x = std::min(min_x, x);
                max_x = std::max(max_x, x);
            }
        }
    }
    if (min_x - 1 >= 0 && max_x + 1 <= width_)
    {
        return std::make_pair(min_x - 1, max_x + 2);
    }
    else
    {
        return std::make_pair(0, width_ + 1);
    }
}

std::pair<int, int> Container::findMinMaxY() const {
    int min_y = 0, max_y = height_;

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            if (grid_[x][y]) {
                min_y = std::min(min_y, y);
                max_y = std::max(max_y, y);
            }
        }
    }

    if (min_y - 1 >= 0 && max_y + 1 <= height_)
    {
        return std::make_pair(min_y - 1, max_y + 2);
    }
    else
    {
        return std::make_pair(0, height_ + 1);
    }
}