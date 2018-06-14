#ifndef SNAKE_H_IS_INCLUDED
#define SNAKE_H_IS_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

struct SnakeSegment{
    SnakeSegment(int x_, int y_) : x(x_), y(y_) {}
    int x; 
    int y;
};	

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction{ None, Up, Down, Left, Right };

class Snake : public sf::Drawable {
public:
    Snake(int blockSize);
    ~Snake(){}

    void setDirection(Direction dir){ mdir = dir; }
    Direction getDirection() const { return mdir; }

    sf::Vector2i getPosition();

    int  getLives() const { return mlives; }
    int  getScore() const { return mscore; }
    int  getSpeed() const { return mspeed; }
    int  getSize()  const { return msize;  }
    void increaseScore(){ mscore += 10; }

    bool hasLost() const {return mlost; }
    void lose(){ mlost = true; } // Igra je izgubljena 
    void toggleLost(){ mlost = !mlost; }

    void extend();   // Povećaj zmiju za jedan blok.
    void reset();    // Vrati zmiju na startnu startnu poziciju.
    void update();   // Update metoda.
    void cut(int n); // Odsjeci zadnjih n segmenata.
    bool checkCollision( const sf::CircleShape& b );

private:
    void move();     // Pomakni zmiju za jedan blok u danom smjeru.
    void checkCollision(); // Provjeri samopresjecanje i napravi odgovarajuću radnju.

    SnakeContainer mSnakeBody; // Segment vector.
    int msize;      // Veličina jednog bloka zmije.
    Direction mdir; // Trenutni smjer kretanja.
    int mspeed;     // Brzina zmije.
    int mlives;     // Broj preostalih života.
    int mscore;     // Postignuti bodovi.
    bool mlost;     // Zastavica za kraj igre.

    mutable sf::RectangleShape mbodyRect; // blok u tijelu zmije - služi za iscrtavanje zmije
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // iscrtavanje
};
#endif
