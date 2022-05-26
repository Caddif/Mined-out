#include "TextHandler.h"

TextHandler::TextHandler(std::string str, int charSize, sf::Vector2f position)
{
    font.loadFromFile("font.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setString(str);
    text.setCharacterSize(charSize);
    text.setPosition(position);
}

TextHandler::~TextHandler() {}

void TextHandler::render(sf::RenderTarget& target) { target.draw(text); }
