//Filename: pointHandle.h
//
//Class deciding whether a given cell should live
//
//Author: Bartosz Paszkiewicz

#pragma once

#include "container.h"

class PointHandle {
public:
    PointHandle(const Container& container);

    bool shouldCellLive(int x, int y) const;

private:
    const Container& container_;

    int countLiveNeighbors(int x, int y) const;
};
