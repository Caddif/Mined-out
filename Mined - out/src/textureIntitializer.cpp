#include "textureIntitializer.h"

TextureIntitializer::TextureIntitializer() {}

TextureIntitializer::~TextureIntitializer() {}

void TextureIntitializer::initializeTexture(std::string file)
{
    if(!texture.loadFromFile(file))  std::cout << "could not find a file" << std::endl;
}

void TextureIntitializer::initializeSprite() { sprite.setTexture(this->texture); }

void TextureIntitializer::render(sf::RenderTarget& window) { window.draw(sprite); }
