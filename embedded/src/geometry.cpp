#include "geometry.h"
#include <algorithm>
#include <vector>

Direction opposite(const Direction& direction) {
    switch (direction) {
        case UP: return DOWN;
        case DOWN: return UP;
        case LEFT: return RIGHT;
        case RIGHT: return LEFT;
    }
}

Direction randomDirection() {
    static std::vector<Direction> directions({UP, DOWN, LEFT, RIGHT});
    return directions[std::rand() % directions.size()];
}

Point Point::random(int maxX, int maxY) {
    return Point {
        std::rand() % maxX,
        std::rand() % maxY,
    };
}
