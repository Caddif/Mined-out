#include "Bomb.h"

Bomb::Bomb(int x, int y) : Entity(x, y)
{
    initializeTexture("textures/bomb.png");
    initializeSprite();
    sprite.setPosition(sf::Vector2f((x * 30), (y * 30)));
}

Bomb::~Bomb() {}
