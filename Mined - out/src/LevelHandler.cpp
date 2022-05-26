#include "LevelHandler.h"

void LevelHandler::newLevel()
{
    LoadLevel("level.txt");
    levelRandomizer();
    int x = rand() % 16;
    LevelTable[x+2][7] = 5;
    x = rand() % 16;
    LevelTable[x+2][23] = 5;
    player.setSpawnPosition();
    bombDetect();
}
