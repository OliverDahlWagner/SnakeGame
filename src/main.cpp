#include <iostream>
#include <ctime>
#include <conio.h>
#include "Game/Game.h"
#include "Renderer/Renderer.h"
#include "Point/Point.h"  

int main() {
    srand(time(NULL));
    Game game;
    Renderer::drawMap(game);

    bool isRunning = true;
    while (isRunning) {

        std::cout << "Enter command (w/a/s/d to move, q to quit): \n";
        char input = _getch();

        Point head = game.getSnake()[0];
        Game::MoveResult result = Game::CONTINUEGAME;

        switch (input) {
        case 'w': result = game.moveSnake({ head.x - 1, head.y }); break;
        case 'a': result = game.moveSnake({ head.x, head.y - 1 }); break;
        case 's': result = game.moveSnake({ head.x + 1, head.y }); break;
        case 'd': result = game.moveSnake({ head.x, head.y + 1 }); break;
        case 'q': isRunning = false; break;
        default: std::cout << "Invalid command!\n";
        }

        if (result == Game::GAMEOVER) {
            std::cout << "Game Over! Final Score: " << game.getSnake().size() - 3 << "\n";
            break;
        }

        Renderer::drawMap(game);
    }

    return 0;
}
