#include "Entity.h"

Entity::Entity(int x, int y, sf::Color color)
{
    entity.setSize(sf::Vector2f(30, 30));
    entity.setPosition(sf::Vector2f((x * 30), (y * 30)));
    entity.setFillColor(color);
}

Entity::Entity(int x, int y) { entity.setPosition(sf::Vector2f((x * 30), (y * 30))); }

Entity::~Entity() {}

sf::FloatRect Entity::area() { return entity.getGlobalBounds(); }

void Entity::render(sf::RenderTarget& target) { target.draw(entity); }
