#ifndef GAME_H
#define GAME_H

#include "Point/Point.h"
#include <vector>
using namespace std;

class Game {
    public:

    static const int ROWS = 10;
    static const int COLS = 20;

    enum MoveResult { CONTINUEGAME, GAMEOVER };

    Game();

    void spawnSnake();
    void spawnFruit();

    bool checkCollision(Point point);
    bool checkFruitCollision(Point point);

    void growSnake(Point point);

    MoveResult moveSnake(Point point);

    const vector<Point>& getSnake() const;
    const vector<Point>& getFruit() const;


    private:
    vector<Point> snake;
    vector<Point> fruit;
};


#endif