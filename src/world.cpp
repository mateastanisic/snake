#include "world.h"
#include <ctime>
#include <random>
#include<iostream>

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(int i=0; i<4; ++i)
      target.draw(mBounds[i]);
    target.draw(mApple);
}

void World::respawnApple(){
    int r=mApple.getRadius();
    int x =rand()%23 + 1;
    int y =rand()%23 + 1;
    mApple.setPosition(x*20,y*20);
}

World::World(sf::Vector2i windowSize){
    mWindowSize=windowSize;
    mBlockSize=20;

    int r=10;
    mApple.setRadius(r);
    mApple.setFillColor(sf::Color::Red);
    //mApple.setOrigin(sf::Vector2f(r/2,r/2));
    respawnApple();

    mBounds[0].setSize(sf::Vector2f(mBlockSize,windowSize.y));

    mBounds[2].setSize(sf::Vector2f(mBlockSize,windowSize.y));
    mBounds[2].setPosition(windowSize.x-mBlockSize,mBounds[2].getPosition().y);

    mBounds[1].setSize(sf::Vector2f(windowSize.x,mBlockSize));

    mBounds[3].setSize(sf::Vector2f(windowSize.x,mBlockSize));
    mBounds[3].setPosition(mBounds[3].getPosition().x,windowSize.y-mBlockSize);
    for(int i=0; i<4; i++ ){
        mBounds[i].setFillColor(sf::Color::Blue);
    }
}

void World::update(Snake &snake){
    sf::RectangleShape glava;
    glava.setPosition(sf::Vector2f(snake.getPosition().x,snake.getPosition().y));
    glava.setSize(sf::Vector2f(snake.getSize(),snake.getSize()));

    for( int i=0; i<4; i++ ){
        if(glava.getGlobalBounds().intersects(mBounds[i].getGlobalBounds())) {
            snake.lose();
            snake.reset();
        }
    }

    if( glava.getGlobalBounds().intersects(mApple.getGlobalBounds()) ){
        //ovdje ne respawnApple(); jer ne želim da se jabuka nalazi negdje na podrucju zmije
        int r,x,y;
        while(1){
            r=mApple.getRadius();
            x =rand()%23 + 1;
            y =rand()%23 + 1;
            sf::CircleShape jabuka;
            jabuka.setRadius(r);
            jabuka.setOrigin(sf::Vector2f(r/2,r/2));
            jabuka.setPosition(sf::Vector2f(20*x,20*y));
            if (!snake.checkCollision(jabuka)) break;
        }
        mApple.setPosition(x*20,y*20);

        snake.increaseScore();
        snake.extend();
    }
}
