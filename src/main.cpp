#include <iostream>
#include <ctime>
#include <conio.h>
#include "Game/Game.h"
#include "Renderer/Renderer.h"
#include "Point/Point.h"  
#include <SFML/Graphics.hpp>

int main() {
    srand(time(NULL));
    Game game;
    bool isRunning = true;
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Snake Game");
    Renderer::drawMap(window, game);

    while (window.isOpen() && isRunning) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::Escape) {
                    isRunning = false;
                    window.close();
                }

                Point head = game.getSnake()[0];
                Game::MoveResult result = Game::CONTINUEGAME;

                switch (keyEvent->code) {
                case sf::Keyboard::Key::W: result = game.moveSnake({ head.x - 1, head.y }); break;
                case sf::Keyboard::Key::A: result = game.moveSnake({ head.x, head.y - 1 }); break;
                case sf::Keyboard::Key::S: result = game.moveSnake({ head.x + 1, head.y }); break;
                case sf::Keyboard::Key::D: result = game.moveSnake({ head.x, head.y + 1 }); break;

                }

                if (result == Game::GAMEOVER) {
                    std::cout << "Game Over! Final Score: " << game.getSnake().size() - 3 << "\n";
                    isRunning = false;
                }
            }
            Renderer::drawMap(window, game);
        }

    }
}
