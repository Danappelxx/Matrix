#pragma once

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

Direction opposite(const Direction& direction);
Direction randomDirection();

struct Point {
    int x, y;

    static Point random(int maxX, int maxY);

    bool operator<(const Point& point) const {
        return x < point.x  || (x == point.x && y < point.y);
    }

    bool operator==(const Point& point) const {
        return x == point.x && y == point.y;
    }
};
