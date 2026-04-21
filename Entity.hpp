#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>

class Entity {
private:
    int x, y;
    int health;

public:
    Entity();

    void move(int dx, int dy);
    void heal(int amount);
    void damage(int amount);
    void reset();
    void status() const;

    int getX() const;
    int getY() const;
    int getHealth() const;
};

#endif