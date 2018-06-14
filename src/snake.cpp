#include "snake.h"

#define START_X 100
#define START_Y 100

Snake::Snake(int blockSize){
    mbodyRect.setSize(sf::Vector2f(blockSize,blockSize));
    msize=blockSize;
    reset();
}

sf::Vector2i Snake::getPosition(){
    return sf::Vector2i(mSnakeBody[0].x,mSnakeBody[0].y);
}

void Snake::extend(){
    int n=mSnakeBody.size();
    int x=mSnakeBody[n-1].x;
    int y=mSnakeBody[n-1].y;
    if( n==1 ){
        if( mdir==Direction::Up){
            SnakeSegment rep(x,y+msize);
            mSnakeBody.push_back(rep);
        }
        else if(mdir==Direction::Down){
            SnakeSegment rep(x,y-msize);
            mSnakeBody.push_back(rep);
        }
        else if(mdir==Direction::Left){
            SnakeSegment rep(x-msize,y);
            mSnakeBody.push_back(rep);
        }
        else if(mdir==Direction::Right){
            SnakeSegment rep(x+msize,y);
            mSnakeBody.push_back(rep);
        }
    }
    else{
        if( (x-mSnakeBody[n-2].x)==0 && (y-mSnakeBody[n-2].y)>0 ){
            SnakeSegment rep(x,y+msize);
            mSnakeBody.push_back(rep);
        }
        else if( (x-mSnakeBody[n-2].x)==0 && (y-mSnakeBody[n-2].y)<0 ){
            SnakeSegment rep(x,y-msize);
            mSnakeBody.push_back(rep);
        }
        else if( (x-mSnakeBody[n-2].x)>0 && (y-mSnakeBody[n-2].y)==0 ){
            SnakeSegment rep(x+msize,y);
            mSnakeBody.push_back(rep);
        }
        else if( (x-mSnakeBody[n-2].x)<0 && (y-mSnakeBody[n-2].y)==0 ){
            SnakeSegment rep(x-msize,y);
            mSnakeBody.push_back(rep);
        }
    }
}

void Snake::reset(){
    mdir=Direction::None;
    mspeed=8;
    mlives=3;
    mlost=false;
    mscore=0;

    mSnakeBody.clear();
    SnakeSegment zmija(START_X,START_Y);//postavljamo na početku zmiju na lokaciju (100,100)
    mSnakeBody.push_back(zmija);
}

void Snake::cut(int n){
    for( int i=0; i<n ; i++)
        mSnakeBody.pop_back();
}

void Snake::checkCollision(){
    sf::RectangleShape body;
    body.setSize(sf::Vector2f(msize,msize));

    sf::RectangleShape glava;
    glava.setSize(sf::Vector2f(msize,msize));
    glava.setPosition(sf::Vector2f(mSnakeBody[0].x,mSnakeBody[0].y));

    int n=mSnakeBody.size();
    for(int i=1; i<n; i++){
        body.setPosition(sf::Vector2f(mSnakeBody[i].x,mSnakeBody[i].y));
        if( glava.getGlobalBounds().intersects(body.getGlobalBounds()) ) {
            cut(n-i);
            mlives--;
            if(mlives==0) { lose(); reset(); }
            break;
        }
    }
}

bool Snake::checkCollision(const sf::CircleShape& b){
    sf::RectangleShape body;
    body.setSize(sf::Vector2f(msize,msize));

    int n=mSnakeBody.size();
    for(int i=0; i<n; i++){
        body.setPosition(sf::Vector2f(mSnakeBody[i].x,mSnakeBody[i].y));
        if( body.getGlobalBounds().intersects(b.getGlobalBounds()) ) {
            return true;
        }
    }
    return false;
}

void Snake::move(){
    if(mdir==Direction::Up){
        int n=mSnakeBody.size();
        for(int i=n-1; i>0 ; i--) {
            mSnakeBody[i].x=mSnakeBody[i-1].x;
            mSnakeBody[i].y=mSnakeBody[i-1].y;
        }
        mSnakeBody[0].y-=msize;
        checkCollision();
    }
    else if(mdir==Direction::Down){
        int n=mSnakeBody.size();
        for(int i=n-1; i>0 ; i--) {
            mSnakeBody[i].x=mSnakeBody[i-1].x;
            mSnakeBody[i].y=mSnakeBody[i-1].y;
        }
        mSnakeBody[0].y+=msize;
        checkCollision();
    }
    else if(mdir==Direction::Left){
        int n=mSnakeBody.size();
        for(int i=n-1; i>0 ; i--) {
            mSnakeBody[i].x=mSnakeBody[i-1].x;
            mSnakeBody[i].y=mSnakeBody[i-1].y;
        }
        mSnakeBody[0].x-=msize;
        checkCollision();
    }
    else if(mdir==Direction::Right){
        int n=mSnakeBody.size();
        for(int i=n-1; i>0 ; i--) {
            mSnakeBody[i].x=mSnakeBody[i-1].x;
            mSnakeBody[i].y=mSnakeBody[i-1].y;
        }
        mSnakeBody[0].x+=msize;
        checkCollision();
    }
}

void Snake::update(){
    if( mdir==Direction::None ) return;
    move();
    checkCollision();
}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    int n=mSnakeBody.size();

    mbodyRect.setFillColor(sf::Color::Green);
    mbodyRect.setPosition(mSnakeBody[0].x,mSnakeBody[0].y);
    target.draw(mbodyRect);

    mbodyRect.setFillColor(sf::Color::Cyan);
    for(int i=1; i<n; ++i){
       mbodyRect.setPosition(mSnakeBody[i].x,mSnakeBody[i].y);
       target.draw(mbodyRect,states);
    }
    return;
}
