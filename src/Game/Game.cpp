#include "Game.h"
#include "Point/Point.h"
#include <iostream>

Game::Game() {
    spawnSnake();
    spawnFruit();
}

void Game::spawnSnake() {
    snake.clear();
    snake.push_back({ 5, 5 });
    snake.push_back({ 5, 4 });
    snake.push_back({ 5, 3 });
}

void Game::spawnFruit() {
    int fruitRow = rand() % ROWS;
    int fruitCol = rand() % COLS;

    while (checkCollision({ fruitRow, fruitCol }) || checkFruitCollision({ fruitRow, fruitCol })) {
        fruitRow = rand() % ROWS;
        fruitCol = rand() % COLS;
    }

    fruit.push_back({ fruitRow, fruitCol });
}

Game::MoveResult Game::moveSnake(Point point) {
    if (point.x < 0 || point.x >= ROWS || point.y < 0 || point.y >= COLS) {
        std::cout << "You hit a wall! Game over.\n";
        return GAMEOVER;
    }

    for (size_t i = 1; i < snake.size(); i++) {
        if (point.x == snake[i].x && point.y == snake[i].y) {
            std::cout << "You hit yourself! Game over.\n";
            return GAMEOVER;
        }
    }

    if (checkFruitCollision(point)) {
        growSnake(point);
    }
    else {
        snake.insert(snake.begin(), point);
        snake.pop_back();
    }

    return CONTINUEGAME;
}

bool Game::checkCollision(Point point) {
    if (point.x <= 0 || point.x >= ROWS - 1 || point.y <= 0 || point.y >= COLS - 1)
        return true;

    for (size_t i = 1; i < snake.size(); i++) {
        if (point.x == snake[i].x && point.y == snake[i].y)
            return true;
    }
    return false;
}

bool Game::checkFruitCollision(Point point) {
    for (const Point& f : fruit) {
        if (point.x == f.x && point.y == f.y) {
            return true;
        }
    }
    return false;
}

void Game::growSnake(Point point) {
    snake.insert(snake.begin(), point);
    fruit.erase(fruit.begin());
    spawnFruit();
}

const std::vector<Point>& Game::getSnake() const {
    return snake;
}

const std::vector<Point>& Game::getFruit() const {
    return fruit;
}