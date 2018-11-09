#include "snake.h"
#include <algorithm>

Snake::Snake(int height, int width) {
    this->aiEnabled = true;
    this->height = height;
    this->width = width;
    reset();
}

void Snake::reset() {
    points = std::vector<Point>({{0, 0}, {1, 0}, {2, 0}, {3, 0}});
    direction = RIGHT;
    food = generateFood();
}

void Snake::setDirection(const Direction& direction) {
    Direction oldDirection = this->direction;
    this->direction = direction;

    // if going in this direction would be going backwards, undo
    if (points.size() >= 2 && points.at(points.size() - 2) == next()) {
        this->direction = oldDirection;
    }
}

void Snake::setAIEnabled(bool aiEnabled) {
    this->aiEnabled = aiEnabled;
}

Point Snake::next() {
    Point head = points.back();
    Point point;
    switch (direction) {
    case UP:
        point = { head.x, head.y + 1 }; break;
    case DOWN:
        point = { head.x, head.y - 1 }; break;
    case LEFT:
        point = { head.x - 1, head.y }; break;
    case RIGHT:
        point = { head.x + 1, head.y }; break;
    }

    if (point.x < 0) { point.x = width - 1; }
    if (point.x == width) { point.x = 0; }
    if (point.y < 0) { point.y = height - 1; }
    if (point.y == height) { point.y = 0; }

    return point;
}

Point Snake::generateFood() {
    Point point;
    do {
        point = Point::random(width, height);
    } while (std::find(points.begin(), points.end(), point) != points.end());
    return point;
}

bool Snake::isGameOver() {
    // if the snake contains the next point, game is over
    return std::find(points.begin(), points.end(), next()) != points.end();
}

int Snake::getLength() const {
    return points.size();
}

void Snake::step() {
    if (isGameOver())
        return reset();

    // move to the next point
    points.push_back(next());
    // if we're on food, generate a new one
    // otherwise, delete our tail (like an inchworm)
    if (next() == food) {
        food = generateFood();
    } else {
        points.erase(points.begin());
    }

    if (aiEnabled) {
        // 4/5 times, move in the right direction
        if (std::rand() % 5 != 0) {
            setDirection(directionTowardsFood());
            // if the "right" direction kills itself (it can happen), move randomly
            if (!isGameOver())
                return;
        }
        // give it 100 guesses to not kill itself lol
        for (int i = 0; i < 100; i++) {
            setDirection(randomDirection());
            if (!isGameOver())
                break;
        }
    }
}

Direction Snake::directionTowardsFood() {
    Point head = this->points.back();
    Point food = this->food;

    Direction xDirection;
    Direction yDirection;

    // x = LEFT or RIGHT
    if (head.x > food.x)
        xDirection = LEFT;
    else
        xDirection = RIGHT;

    // y = UP or DOWN
    if (head.y > food.y)
        yDirection = DOWN;
    else
        yDirection = UP;

    int xDiff = abs(head.x - food.x);
    int yDiff = abs(head.y - food.y);

    // make sure we dont run into ourselves
    if (xDiff > yDiff && xDirection)
        return xDirection;
    else
        return yDirection;
}

void Snake::draw(Matrix* matrix) {
    matrix->clear();

    for (const Point& point : points) {
        matrix->set(point, Color { 200, 200, 0 });
    }

    matrix->set(food, Color { 255, 75, 0 });
}
