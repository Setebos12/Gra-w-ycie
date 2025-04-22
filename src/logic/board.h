#pragma once

#include "GameObject.h"
#include "Container.h"
#include "PointHandle.h"
#include <memory>

class Board : public GameObject {
public:
    Board(const std::string& name, int width, int height);

    void draw(const Drawer& drawer) override;
    void update() override;

    void toggleCellState(int x, int y);
    void resetBoard();
    int getGenerationCount() const;

private:
    std::unique_ptr<Container> container_;
    int generationCount_;

    void incrementGeneration();
};