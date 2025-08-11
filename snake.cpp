#include <iostream>
#include <array>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

void mapSetup();
void drawMap();
void spawnFruit();
void spawnPlayer();
void gameTick();
bool checkCollision(Point point);
bool checkFruitCollision(Point point);
void growSnake(Point point);
void snakeMovement(Point point);


const int ROWS = 20;
const int COLS = 40;

char map[ROWS][COLS];

vector<Point> snake;
vector<Point> fruit;

enum MoveResult { CONTINUEGAME, GAMEOVER };

MoveResult moveSnake(Point point) {

    if (point.x <= 0 || point.x >= ROWS - 1 || point.y <= 0 || point.y >= COLS - 1) {
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

int main() {
    srand(time(NULL));
    spawnPlayer();
    spawnFruit();

    drawMap();

    bool isRunning = true;
    while (isRunning) {
        char input;
        std::cout << "Enter command (w/a/s/d to move, q to quit): ";
        std::cin >> input;

        Point head = snake[0];
        MoveResult result = CONTINUEGAME;

        switch (input) {
        case 'w': {
            result = moveSnake({ head.x - 1, head.y });
            break;
        }
        case 'a':
            result = moveSnake({ head.x, head.y - 1 });
            break;
        case 's':
            result = moveSnake({ head.x + 1, head.y });
            break;
        case 'd':
            result = moveSnake({ head.x, head.y + 1 });
            break;
        case 'q':
            isRunning = false;
            break;
        default:
            std::cout << "Invalid command!\n";
        }

        if (result == GAMEOVER) {
            isRunning = false;
            std::cout << "Game Over! Final Score: " << snake.size() - 3 << "\n";
            break;
        }


        drawMap();
    }

    return 0;
}


void mapSetup() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            map[i][j] = ' ';
        }
    }

    for (int i = 0; i < ROWS; i++) {
        map[i][0] = '#'; // left wall
        map[i][COLS - 1] = '#'; // right wall
    }

    for (int j = 0; j < COLS; j++) {
        map[0][j] = '#'; // top wall
        map[ROWS - 1][j] = '#'; // bottom wall
    }

    drawMap();
}

void spawnPlayer() {

    snake.push_back({ 5, 5 });
    snake.push_back({ 5, 4 });
    snake.push_back({ 5, 3 });
}

void drawMap() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            map[i][j] = ' ';
        }
    }

    for (int i = 0; i < ROWS; i++) {
        map[i][0] = '#';
        map[i][COLS - 1] = '#';
    }

    for (int j = 0; j < COLS; j++) {
        map[0][j] = '#';
        map[ROWS - 1][j] = '#';
    }

    for (const Point& segment : snake) {
        map[segment.x][segment.y] = '0';
    }

    for (const Point& f : fruit) {
        map[f.x][f.y] = 'X';
    }
    // Print the map
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << map[i][j];
        }
        std::cout << '\n';
    }
}

void spawnFruit() {

    int fruitRow = rand() % ROWS;
    int fruitCol = rand() % COLS;

    while (map[fruitRow][fruitCol] == '0' || map[fruitRow][fruitCol] == '#') {
        fruitRow = rand() % ROWS;
        fruitCol = rand() % COLS;
    }

    fruit.push_back({ fruitRow, fruitCol });
}

bool checkCollision(Point point) {

    if (point.x <= 0 || point.x >= ROWS - 1 || point.y <= 0 || point.y >= COLS - 1) {
        std::cout << "You hit a wall! Game over.\n";
        return true;
    }

    for (size_t i = 1; i < snake.size(); i++) {
        if (point.x == snake[i].x && point.y == snake[i].y) {
            std::cout << "You hit yourself! Game over.\n";
            return true;
        }
    }

    return false;
}

bool checkFruitCollision(Point point) {
    for (const Point& f : fruit) {
        if (point.x == f.x && point.y == f.y) {
            std::cout << "You ate a fruit!\n";
            return true;
        }
    }
    return false;
}

void growSnake(Point point) {
    snake.insert(snake.begin(), point);
    fruit.erase(fruit.begin());
    spawnFruit();
}

void snakeMovement(Point point) {
    Point head = snake[0];

    if (point.x < 0 || point.x >= ROWS || point.y < 0 || point.y >= COLS) {
        std::cout << "You hit a wall! Game over.\n";
        return;
    }

    for (size_t i = 1; i < snake.size(); i++) {
        if (point.x == snake[i].x && point.y == snake[i].y) {
            std::cout << "You hit yourself! Game over.\n";
            return;
        }
    }

    if (checkFruitCollision(point)) {
        growSnake(point);
    }
    else {
        snake.insert(snake.begin(), point);
        snake.pop_back();
    }
}