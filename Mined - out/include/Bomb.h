#ifndef BOMB_H
#define BOMB_H
#include <Entity.h>
#include <TextureIntitializer.h>

class Bomb : public Entity, public TextureIntitializer
{
public:
    Bomb(int x, int y);
    ~Bomb();
};

#endif // BOMB_H
