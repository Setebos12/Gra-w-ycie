#pragma once

#include "Container.h"

class PointHandle {
public:
    PointHandle(const Container& container);

    bool shouldCellLive(int x, int y) const;

private:
    const Container& container_;

    int countLiveNeighbors(int x, int y) const;
};
