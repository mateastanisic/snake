#ifndef GAME_V1_H_INCLUDED
#define GAME_V1_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "snake.h"
#include "world.h"

class Game{
public:
    Game();
    void run();
private:
    void processEvents();
    void update(sf::Time dt);
    void render();
private:
    sf::RenderWindow mWindow;
    World mWorld;
    Snake mSnake;
    sf::Time mTimePerFrame;

    void handlePlayerInput(sf::Keyboard::Key code);
};

#endif // GAME-V1_H_INCLUDED
