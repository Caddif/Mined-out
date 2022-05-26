#ifndef PLAYER_H
#define PLAYER_H
#include <TextureIntitializer.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>

class Player : public TextureIntitializer
{
public:
    unsigned int key = 2;
    float posx = 0;
    float posy = 0;

    Player();
    ~Player();

    void initializePlayer();
    void handleInput();
    void movePlayer(float dirX, float dirY);
    void setSpawnPosition();
    void setcurrentPosition(float x, float y);

    sf::FloatRect area();
    sf::Vector2f getPosition();
};

#endif // PLAYER_H
