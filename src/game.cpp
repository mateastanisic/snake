#include "game.h"

#define SCRWIDTH 500
#define SCRHEIGHT 500

Game::Game() : mWindow(sf::VideoMode(SCRWIDTH,SCRHEIGHT), "Snake") , mWorld({SCRWIDTH,SCRHEIGHT}) , mSnake(20){
    mTimePerFrame=sf::seconds(1.0f/mSnake.getSpeed()); //t=s/v
}

void Game::run(){
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow.isOpen())
    {
       processEvents();
       timeSinceLastUpdate += clock.restart();
       while(timeSinceLastUpdate > mTimePerFrame)
       {
          timeSinceLastUpdate -= mTimePerFrame;
          processEvents();
          update(mTimePerFrame);
          if(mSnake.hasLost()) mSnake.reset();
       }
       render();
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key code){
    if( code == sf::Keyboard::Up) {
        if( mSnake.getDirection()==Direction::Down ) return;
        else mSnake.setDirection(Direction::Up);
    }
    if( code == sf::Keyboard::Down){
        if( mSnake.getDirection()==Direction::Up ) return;
        else mSnake.setDirection(Direction::Down);
    }
    if( code == sf::Keyboard::Left) {
        if( mSnake.getDirection()==Direction::Right ) return;
        else mSnake.setDirection(Direction::Left);
    }
    if( code == sf::Keyboard::Right) {
        if( mSnake.getDirection()==Direction::Left ) return;
        else mSnake.setDirection(Direction::Right);
    }
}

void Game::processEvents(){
    sf::Event event;
    while(mWindow.pollEvent(event)){
      switch(event.type){
        case sf::Event::Closed:
          mWindow.close();
          break;
        case sf::Event::KeyPressed:
          handlePlayerInput(event.key.code);
          break;
      }
    }
}

void Game::update(sf::Time dt){
    mSnake.update();
    mWorld.update(mSnake);
}

void Game::render(){
    mWindow.clear();
    mWindow.draw(mWorld);
    mWindow.draw(mSnake);
    mWindow.display();
}
