#pragma once

#include <vector>

class Container {
public:
    Container(int width, int height);

    bool getCellState(int x, int y) const;
    void setCellState(int x, int y, bool state);
    int getWidth() const;
    int getHeight() const;

private:
    std::vector<std::vector<bool>> grid_;
    int width_;
    int height_;
};
