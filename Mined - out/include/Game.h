#ifndef GAME_H
#define GAME_H
#include <Player.h>
#include <Entity.h>
#include <Bomb.h>
#include <TextHandler.h>
#include <TextureIntitializer.h>

class Game : public TextureIntitializer
{
private:
    bool win = false;
    unsigned int sumOfbombs = 0;
    int level = 0;

    void windowSetup();
    void texthandler();

public:
    sf::RenderWindow window;
    Player player;
    int LevelTable[22][32];
    friend class LevelHandler;

    Game();
    ~Game();
    void runNew();
    void runOld();
    void menu();
    void update();
    void render();
    void LoadLevel(std::string level);
    void showLevel();
    void gameLogic();
    void finish();
    void bombDetect();
    void levelRandomizer();
    void newLevel();
    void renderBombfield();
    void saveMap(std::string game);
    void loadMap(std::string game);
    void saveData(std::string game);
    void loadData(std::string game);
};

#endif // GAME_H
