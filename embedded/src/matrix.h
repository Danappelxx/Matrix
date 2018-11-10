#pragma once

#include "color.h"
#include "geometry.h"
#include <map>
#include <vector>

class Matrix {
public:
    Matrix(int height, int width);
    int getHeight();
    int getWidth();
    void set(Point point, Color color);
    void clear();
    std::vector<Color> getStrip();
private:
    // translates cartesian point to index on strip
    int translate(Point point);
    std::map<Point, Color> points;
    int height, width;
};
