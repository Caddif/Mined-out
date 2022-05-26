#ifndef TEXTUREINTITIALIZER_H
#define TEXTUREINTITIALIZER_H
#include <SFML/Graphics.hpp>
#include <iostream>

class TextureIntitializer
{
protected:
    sf::Sprite sprite;
    sf::Texture texture;

    void initializeTexture(std::string file);
    void initializeSprite();

public:
    void render(sf::RenderTarget& window);
    TextureIntitializer();
    virtual ~TextureIntitializer() = 0;
};

#endif // TEXTUREINTITIALIZER_H
