#pragma once

#include "board.h"
#include <utility>

Board::Board(const std::string& name, int width, int height)
	: GameObject(name),
	container(std::make_unique<Container>(width, height)),
	pointHandle(std::make_unique<PointHandle>(*container)),
	generationCount(0) {}

Board::update()
{
	if (!container || !pointHandle) return;

	int width = container->getWidth();
	int height = container->getHeight();

	std::vector<std::pair<int, int>> cellsToToggle;

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			if (container->getCellState(x, y) != pointHandle->shouldCellLive(x, y))
			{
				cellsToToggle.emplace_back({x, y});
			}
		}
	}

	for (auto& cell : cellsToToggle)
	{
		toggleCellState(cell.first, cell.second);
	}

	incrementGeneration();
}

void Board::toggleCellState(int x, int y)
{
	bool currentState = container->getCellState(x, y);
	container->setCellState(x, y, !currentState);
}

void Board::resetBoard()
{
	container->resetContainer();
}

int Board::getGenerationCount() const
{
	return generationCount;
}

void Board::incrementGeneration()
{
	generationCount++;
}