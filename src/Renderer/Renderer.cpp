#include "Renderer/Renderer.h"
#include "Game/Game.h"
#include "Point/Point.h"
#include <iostream>

void Renderer::drawMap(const Game& game) {
    char map[Game::ROWS][Game::COLS];

    for (int i = 0; i < Game::ROWS; i++)
    {
        for (int j = 0; j < Game::COLS; j++)
        {
            map[i][j] = ' ';
        }
    }

    for (int i = 0; i < Game::ROWS; i++)
    {
        map[i][0] = '#';
        map[i][Game::COLS - 1] = '#';
    }

    for (int i = 0; i < Game::COLS; i++)
    {
        map[0][i] = '#';
        map[Game::ROWS - 1][i] = '#';
    }

    for (const Point& segment : game.getSnake()) {
        map[segment.x][segment.y] = '0';
    }

    for (const Point& fruit : game.getFruit()) {
        map[fruit.x][fruit.y] = 'X';
    }

    for (int i = 0; i < Game::ROWS; i++)
    {
        for (int j = 0; j < Game::COLS; j++)
        {
            cout << map[i][j];
        }
        cout << '\n';

    }

}