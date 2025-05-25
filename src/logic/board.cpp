#include "board.h"
#include <utility>
#include <sstream>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <iostream>

template<typename T>
std::string toString(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

Board::Board(const std::string& name, int width, int height, std::shared_ptr<Util::Event<const std::string&, Util::Level>>& logEvent)
	: GameObject(name, logEvent),
	container(std::make_unique<Container>(width, height)),
	pointHandle(std::make_unique<PointHandle>(*container)),
	generationCount(0) {}

void Board::update()
{
	if (!container || !pointHandle) return;

	int width = container->getWidth();
	int height = container->getHeight();

	int min_x = container->findMinMaxX().first;
	int max_x = container->findMinMaxX().second;

	int min_y = container->findMinMaxY().first;
	int max_y = container->findMinMaxY().second;

	std::vector<std::pair<int, int>> cellsToToggle;

	for (int x = min_x; x < max_x; ++x)
	{
		for (int y = min_y; y < max_y; ++y)
		{
			if (container->getCellState(x, y) != pointHandle->shouldCellLive(x, y))
			{
				cellsToToggle.push_back(std::make_pair(x, y));
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

void Board::draw(Render::Drawer& drawer) {
    if (!container) return;

    float cellSize = 10.0f;

    for (int x = 0; x < container->getWidth(); ++x) {
        for (int y = 0; y < container->getHeight(); ++y) {
            bool alive = container->getCellState(x, y);

            sf::Vector2f position(x * cellSize, y * cellSize);
            sf::Vector2f size(cellSize, cellSize);
            sf::Color color = alive ? sf::Color::Green : sf::Color::Black;

            drawer.drawRect(position, size, color);
        }
    }
}

std::string Board::printString() const {
    std::string result;

    int aliveCount = 0;
    std::string gridData;

    int width = container->getWidth();
    int height = container->getHeight();

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            bool alive = container->getCellState(x, y);
            if (alive) aliveCount++;
            gridData += alive ? '1' : '0';
        }
    }

    result += toString(width) + " ";
    result += toString(height) + " ";
    result += toString(generationCount) + " ";
    result += toString(aliveCount) + " ";
    result += gridData;

    return result;
}

void Board::readString(const std::string& read) {
    std::istringstream iss(read);
    int width, height, generation, aliveCount;
    iss >> width >> height >> generation >> aliveCount;

    container = std::make_unique<Container>(width, height);
    pointHandle = std::make_unique<PointHandle>(*container);
    generationCount = generation;

    std::string gridData;
    iss >> gridData;

    int index = 0;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (index < gridData.size()) {
                bool state = gridData[index++] == '1';
                container->setCellState(x, y, state);
            }
        }
    }
}
