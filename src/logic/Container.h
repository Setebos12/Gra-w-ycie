#pragma once

#include <vector>

class Container {
public:
    Container(int width, int height);

    bool getCellState(int x, int y) const;
    void setCellState(int x, int y, bool state);
    int getWidth() const;
    int getHeight() const;
    void resetContainer();

private:
    std::vector<std::vector<bool>> grid;
    int width;
    int height;
};
