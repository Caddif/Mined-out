#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H
#include <Entity.h>

class TextHandler
{
private:
    sf::Text text;
    sf::Font font;

public:
    TextHandler(std::string str, int charSize, sf::Vector2f position);
    ~TextHandler();
    void render(sf::RenderTarget& target);
};

#endif // TEXTHANDLER_H
