#include "matrix.h"

Matrix::Matrix(int height, int width) {
    this->height = height;
    this->width = width;
    this->points = std::map<Point, Color>();
}

int Matrix::getHeight() {
    return height;
}

int Matrix::getWidth() {
    return width;
}

void Matrix::set(Point point, Color color) {
    points[point] = color;
}

void Matrix::clear() {
    points = std::map<Point, Color>();
}

std::vector<Color> Matrix::getStrip() {
    std::vector<Color> strip(getWidth() * getHeight());

    // fill with blanks
    for (auto i = 0; i < strip.size(); i++) {
        strip[i] = Color { 7, 0, 14 };
    }

    for (auto const& pointColor : points) {
        strip[translate(pointColor.first)] = pointColor.second;
    }

    return strip;
}

int Matrix::translate(Point point) {
    // bottom left corner = (0,0)
    // top right corner = (width - 1, height - 1)
    if (point.x >= getWidth() || point.y >= getHeight())
        return -1;

    // skip Y number of strips
    int y_offset = point.y * getWidth();
    int x_offset;
    if (point.y % 2 == 1)
        x_offset = getWidth() - 1 - point.x;
    else
        x_offset = point.x;
    return y_offset + x_offset;
}
