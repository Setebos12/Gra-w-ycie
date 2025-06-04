//Filename: board.cpp
//
// Implements board methods
//
//Author: Bartosz Paszkiewicz

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

Board::Board(const std::string& name,
             int width, int height,
             std::shared_ptr<Util::Event<const std::string&, Util::Level>>& logEvent)
    : GameObject(name, logEvent, true),
    container_(std::make_unique<Container>(width, height)),
    pointHandle_(std::make_unique<PointHandle>(*container_)),
    generationCount_(0) {
}

void Board::update()
{
    if (!container_ || !pointHandle_) return;

    int width = container_->getWidth();
    int height = container_->getHeight();

    int min_x = container_->findMinMaxX().first;
    int max_x = container_->findMinMaxX().second;

    int min_y = container_->findMinMaxY().first;
    int max_y = container_->findMinMaxY().second;

    std::vector<std::pair<int, int>> cellsToToggle;

    for (int x = min_x; x < max_x; ++x)
    {
        for (int y = min_y; y < max_y; ++y)
        {
            if (container_->getCellState(x, y) != pointHandle_->shouldCellLive(x, y))
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
    bool currentState = container_->getCellState(x, y);
    container_->setCellState(x, y, !currentState);
}

void Board::resetBoard()
{
    container_->resetContainer();
}

int Board::getGenerationCount() const
{
    return generationCount_;
}

void Board::incrementGeneration()
{
    ++generationCount_;
    updateGenEvent_.invoke(generationCount_);
}

void Board::draw(Render::Drawer& drawer) {
    if (!container_) return;

    float cellSize = 10.0f;

    for (int x = 0; x < container_->getWidth(); ++x) {
        for (int y = 0; y < container_->getHeight(); ++y) {
            bool alive = container_->getCellState(x, y);

            sf::Vector2f position(x * cellSize, y * cellSize);
            sf::Vector2f size(cellSize, cellSize);
            sf::Color color = alive ? sf::Color::Green : sf::Color::Blue;

            drawer.drawRect(position, size, color);
        }
    }
}

std::string Board::printString() const {
    std::string result;

    int aliveCount = 0;
    std::string gridData;

    int width = container_->getWidth();
    int height = container_->getHeight();

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            bool alive = container_->getCellState(x, y);
            if (alive) aliveCount++;
            gridData += alive ? '1' : '0';
        }
    }

    result += toString(width) + " ";
    result += toString(height) + " ";
    result += toString(generationCount_) + " ";
    result += toString(aliveCount) + " ";
    result += gridData;

    return result;
}

void Board::readString(const std::string& read) {
    std::istringstream iss(read);
    int width, height, generation, aliveCount;
    iss >> width >> height >> generation >> aliveCount;

    container_ = std::make_unique<Container>(width, height);
    pointHandle_ = std::make_unique<PointHandle>(*container_);
    generationCount_ = generation;

    std::string gridData;
    iss >> gridData;

    int index = 0;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (index < gridData.size()) {
                bool state = gridData[index++] == '1';
                container_->setCellState(x, y, state);
            }
        }
    }
}

bool Board::input(InputToken& token) {
    if (!inputEnabled_) return false;
    if (!(token.getType() == TokenType::LEFT_MOUSE_DOWN) && !(token.getType() == TokenType::LEFT_MOUSE_PRESSED))
        return false;

    int cellSize = 10;
    sf::Vector2f v1(0.f, 0.f);
    sf::Vector2f v2(container_->getWidth() * cellSize, container_->getHeight() * cellSize);
    sf::FloatRect boardRect(v1, v2);

    sf::FloatRect rect(v1, v2);
    if (!rect.contains(sf::Vector2f(token.getMousePos())))
        return false;

    int x = static_cast<int>((token.getMousePos().x - boardRect.position.x) / cellSize);
    int y = static_cast<int>((token.getMousePos().y - boardRect.position.y) / cellSize);

    if (token.getType() == TokenType::LEFT_MOUSE_PRESSED) {
        erasing_ = container_->getCellState(x, y);
    }

    if (container_->getCellState(x, y) == erasing_)
        toggleCellState(x, y);

    return true;
}