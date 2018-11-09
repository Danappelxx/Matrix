#pragma once

#include "color.h"
#include "geometry.h"
#include "matrix.h"
#include <vector>

class Snake {
public:
    Snake(int height, int width);
    void reset();
    void setDirection(const Direction& direction);
    void setAIEnabled(bool aiEnabled);
    void step();
    void draw(Matrix* matrix);
    int getLength() const;
private:
    Point next();
    Point generateFood();
    bool isGameOver();
    Direction directionTowardsFood();

    std::vector<Point> points;
    Direction direction;
    Point food;
    int height, width;
    bool aiEnabled;
};
