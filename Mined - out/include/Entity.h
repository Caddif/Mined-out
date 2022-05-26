#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity
{
private:
    sf::RectangleShape entity;

public:
    Entity(int x, int y, sf::Color color);
    Entity(int x, int y);
    ~Entity();

    sf::FloatRect area();
    virtual void render(sf::RenderTarget& target);
};

#endif // ENTITY_H
