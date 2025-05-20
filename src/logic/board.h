#pragma once

#include "../core/gameobject.h"
#include "Container.h"
#include "PointHandle.h"
#include <memory>

class Board : public MVC::GameObject {
public:
    Board(const std::string& name, int width, int height);

    void draw(const Render::Drawer& drawer) override;
    void update() override;

    void toggleCellState(int x, int y);
    void resetBoard();
    int getGenerationCount() const;


    std::string printString() const;
    void readString(const std::string& read);

private:
    std::unique_ptr<Container> container;
    std::unique_ptr<PointHandle> pointHandle;
    int generationCount;

    void incrementGeneration();
};
