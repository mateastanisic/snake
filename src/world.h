#ifndef WORLD_H_IS_INCLUDED
#define WORLD_H_IS_INCLUDED

#include <SFML/Graphics.hpp>
#include "snake.h"

class World : public sf::Drawable {
public:
    World(sf::Vector2i windowSize);
    void respawnApple(); // Nova (slučajna) pozicija za jabuku nakon što je pojedena.
    int getBlockSize() const {return mBlockSize; }
    void update(Snake & snake);     // Provjeri je li zmija pojela jabuku ...
private:
    sf::Vector2i mWindowSize;   // Veličina ekrana
    int mBlockSize;             // Veličina  bloka od kog je građena zmija
    sf::CircleShape    mApple;      // jabuka
    sf::RectangleShape mBounds[4];  // rubovi domene
    // iscrtavanje
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
