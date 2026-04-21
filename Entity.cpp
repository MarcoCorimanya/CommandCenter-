#include "Entity.hpp"

Entity::Entity() : x(0), y(0), health(100) {}

void Entity::move(int dx, int dy) {
    x += dx;
    y += dy;
}

void Entity::heal(int amount) {
    health += amount;
}

void Entity::damage(int amount) {
    health -= amount;
}

void Entity::reset() {
    x = 0;
    y = 0;
    health = 100;
}

void Entity::status() const {
    std::cout << "Pos(" << x << "," << y << ") Health: " << health << std::endl;
}

int Entity::getX() const { return x; }
int Entity::getY() const { return y; }
int Entity::getHealth() const { return health; }