#include "Player.h"

Player::Player()
{
    initializeTexture("textures/Player.png");
    initializeSprite();
    setSpawnPosition();
}

Player::~Player() {}

void Player::handleInput()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))  movePlayer(0.f, -30.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))  movePlayer(-30.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))  movePlayer(0.f, 30.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))  movePlayer(30.f, 0.f);
}

sf::FloatRect Player::area() { return sprite.getGlobalBounds(); }

sf::Vector2f Player::getPosition() { return sprite.getPosition(); }

void Player::movePlayer(float dirX, float dirY)
{
    sprite.move(dirX , dirY);
    if(sprite.getPosition().y >= 630)
        sprite.move(-dirX , -dirY);
    if(sprite.getPosition().y < 0)
        sprite.move(-dirX , -dirY);
}

void Player::setSpawnPosition() { sprite.setPosition((930.f/2) - 15.f,630.f - 30.f); }

void Player::setcurrentPosition(float x, float y) { sprite.setPosition(y,x); }
