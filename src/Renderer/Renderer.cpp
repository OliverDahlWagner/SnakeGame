#include "Renderer.h"
#include "Game/Game.h"
#include "Point/Point.h"
#include <iostream>


void Renderer::drawMap(sf::RenderWindow& win, const Game& game) {
    sf::Vector2f size = win.getView().getSize();
    float rowHeight = size.y / static_cast<float>(Game::ROWS);
    float colWidth = size.x / static_cast<float>(Game::COLS);

    sf::RectangleShape playfield({ size.x, size.y });
    playfield.setPosition({ 0.f, 0.f });
    playfield.setFillColor(sf::Color::White);
    win.draw(playfield);

    for (int i = 0; i < game.getSnake().size(); i++)
    {
        sf::RectangleShape cell({ colWidth, rowHeight });
        cell.setPosition({ game.getSnake()[i].y * colWidth, game.getSnake()[i].x * rowHeight });
        if (i == 0) {
            cell.setFillColor(sf::Color::Magenta);
        }
        else {
            cell.setFillColor(sf::Color::Black);
        }
        win.draw(cell);
    }

    for (const Point& fruit : game.getFruit()) {
        sf::RectangleShape cell({ colWidth, rowHeight });
        cell.setPosition({ fruit.y * colWidth, fruit.x * rowHeight });
        cell.setFillColor(sf::Color::Red);
        win.draw(cell);
    }


    sf::VertexArray grid(sf::PrimitiveType::Lines);
    grid.resize(2u * static_cast<unsigned>((Game::ROWS - 1) + (Game::COLS - 1)));
    std::size_t k = 0;
    for (int i = 1; i < Game::ROWS; ++i) {
        float y = i * rowHeight;

        grid[k].position = { 0.f, y };
        grid[k].color = sf::Color::Black; ++k;

        grid[k].position = { size.x, y };
        grid[k].color = sf::Color::Black; ++k;
    }

    for (int j = 1; j < Game::COLS; ++j) {
        float x = j * colWidth;

        grid[k].position = { x, 0.f };
        grid[k].color = sf::Color::Black; ++k;

        grid[k].position = { x, size.y };
        grid[k].color = sf::Color::Black; ++k;
    }

    win.draw(grid);
    win.display();
}
