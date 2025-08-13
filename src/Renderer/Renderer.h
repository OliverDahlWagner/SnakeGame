#ifndef RENDERER_H
#define RENDERER_H

#include "Game/Game.h"
#include <SFML/Graphics.hpp>

class Renderer {
    public:
    static void drawMap(sf::RenderWindow& win, const Game& game);
};

#endif