#include "Game.h"

void Game::windowSetup()
{
    window.create(sf::VideoMode(930, 660), "Mined-out", sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Image icon;
    icon.loadFromFile("textures/Player.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);
}

void Game::texthandler()
{
    std::string bombNumber = std::to_string(sumOfbombs);

    TextHandler bombtext("Number of bombs:", 24, sf::Vector2f(10,633));
    bombtext.render(window);

    TextHandler bombs(bombNumber, 24, sf::Vector2f(280,633));
    bombs.render(window);
}

Game::Game(){ windowSetup(); }

Game::~Game() {}

void Game::runNew()
{
    player.setSpawnPosition();
    levelRandomizer();
    player.key = 2;
    level = 0;
    sumOfbombs = 0;
    while(window.isOpen() && win == false)
    {
        update();
        render();
    }
}

void Game::runOld()
{
    player.setSpawnPosition();
    loadMap("save.txt");
    loadData("data.txt");
    player.setcurrentPosition(player.posy * 30, player.posx * 30);
    sumOfbombs = 0;
    bombDetect();
    while(window.isOpen() && win == false)
    {
        update();
        render();
    }
}

void Game::menu()
{
    LoadLevel("level.txt");
    initializeTexture("textures/menu.png");
    initializeSprite();
    sf::Event ev;
    while(window.isOpen())
    {
        window.clear();
        window.draw(sprite);
        while(window.pollEvent(ev))
        {
            if(ev.Event::type == sf::Event::Closed) window.close();
            else if(ev.Event::type == sf::Event::EventType::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
            else if(ev.Event::type == sf::Event::EventType::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) runOld();
            else if(ev.Event::type == sf::Event::EventType::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::N)) runNew();
        }
        window.display();
    }
}

void Game::update()
{
    sf::Event ev;
    if(window.waitEvent(ev))
    {
        if(ev.Event::type == sf::Event::Closed)
        {
            saveMap("save.txt");
            saveData("data.txt");
            window.close();
        }
        else if(ev.Event::type == sf::Event::EventType::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            saveMap("save.txt");
            saveData("data.txt");
            menu();
        }
        else if(ev.Event::type == sf::Event::EventType::KeyPressed)
        {
            sumOfbombs = 0;
            player.handleInput();
            bombDetect();
            gameLogic();
        }
    }
}

void Game::render()
{
    window.clear();
    showLevel();
    texthandler();
    player.render(window);
    window.display();
}

void Game::LoadLevel(std::string level)
{
    std::ifstream file(level);
    if(file.is_open() && !file.eof())
    {
        for(int i = 0; i < 22; i++)
        {
            for(int j = 0; j < 32; j++)
            {
                int x = file.get() - 48;
                LevelTable[i][j] = x;
            }
        }
    }
    else{ std::cout << "Error: File cannot be opened" << std::endl; }
    file.close();
}

void Game::showLevel()
{
    for(int i = 0; i < 21; i++)
    {
        for(int j = 0; j < 31; j++)
        {
            int x = LevelTable[i][j];
            if(x == 1)
            {
                Entity wall(j, i, sf::Color::Red);
                wall.render(window);
            }
            else if(x == 3)
            {
                Entity trail(j, i, sf::Color::White);
                trail.render(window);
            }
            else if(x == 5)
            {
                Entity collectable(j, i, sf::Color::Cyan);
                collectable.render(window);
            }
        }
    }
}

void Game::gameLogic()
{
    for(int i = 0; i < 21; i++)
    {
        for(int j = 0; j < 31; j++)
        {
            int x = LevelTable[i][j];
            if(j == player.getPosition().x/30 && i == player.getPosition().y/30 && LevelTable[i][j] == 0)  LevelTable[i][j] = 3;
            if(x == 1)
            {
                Entity wall(j, i, sf::Color::Red);
                if(wall.area().intersects(player.area())) player.setSpawnPosition();
            }
            else if(x == 2)
            {
                Entity bomb(j, i, sf::Color::Cyan);
                if(bomb.area().intersects(player.area()))
                {
                    finish();
                }
            }
            else if(x == 4)
            {
                if(j == player.getPosition().x/30 && i == player.getPosition().y/30 && player.key == 2)
                {
                    newLevel();
                    player.key = 0;
                    level = level + 1;
                    if(level == 2)
                    {
                        win = true;
                        finish();
                    }
                }
            }
            else if(x == 5)
            {
                Entity collectable(j, i, sf::Color::Cyan);
                if(player.area().intersects(collectable.area()))
                {
                    player.key = player.key + 1;
                    LevelTable[i][j] = 3;
                }
            }
        }
    }
}

void Game::finish()
{
    if(win == true)
    {
        TextHandler text("Congratulations you won!", 24, sf::Vector2f(520, 633));
        text.render(window);
    }
    else
    {
        renderBombfield();
        TextHandler text("GAME OVER", 24, sf::Vector2f(520, 633));
        text.render(window);
    }
    window.display();
    sf::Event ev;
    while(window.isOpen())
    {
        if(window.waitEvent(ev))
        {
            if(ev.Event::type == sf::Event::Closed)
            {
                player.setSpawnPosition();
                bombDetect();
                window.close();
            }
            else if(ev.Event::type == sf::Event::EventType::KeyPressed)
            {
                player.setSpawnPosition();
                levelRandomizer();
                bombDetect();
                saveMap("save.txt");
                saveData("data.txt");
                menu();
            }
        }
    }
}

void Game::bombDetect()
{
    float x = player.getPosition().x/30;
    float y = player.getPosition().y/30;
    player.posx = x;
    player.posy = y;
    int xc = static_cast<int>(x);
    int yc = static_cast<int>(y);
    if(LevelTable[yc+1][xc] == 2) sumOfbombs = sumOfbombs + 1;
    if(LevelTable[yc-1][xc] == 2) sumOfbombs = sumOfbombs + 1;
    if(LevelTable[yc][xc+1] == 2) sumOfbombs = sumOfbombs + 1;
    if(LevelTable[yc][xc-1] == 2) sumOfbombs = sumOfbombs + 1;
}

void Game::levelRandomizer()
{
    for(int i = 1; i < 20; i++)
    {
        for(int j = 1; j < 30; j++)
        {
            int x = rand() % 9;
            LevelTable[i][j] = x;
            if(LevelTable[i][j] != 2) LevelTable[i][j] = 0;
        }
    }
    //constraints for a level to be playable
    LevelTable[19][14] = 0;
    LevelTable[19][15] = 0;
    LevelTable[19][16] = 0;
    LevelTable[1][14] = 0;
    LevelTable[1][15] = 0;
    LevelTable[1][16] = 0;
}

void Game::newLevel()
{
    LoadLevel("level.txt");
    levelRandomizer();
    int x = rand() % 16;
    LevelTable[x+2][7] = 5;
    x = rand() % 16;
    LevelTable[x+2][23] = 5;
    player.setSpawnPosition();
}

void Game::renderBombfield()
{
    for(int i = 1; i < 20; i++)
    {
        for(int j = 1; j < 30; j++)
        {
            int x = LevelTable[i][j];
            if(x == 2)
            {
                Bomb field(j, i);
                field.TextureIntitializer::render(window);
            }
        }
    }
}

void Game::saveMap(std::string game)
{
    std::fstream save;
    save.open(game, std::ios::out);
    if(save.is_open())
    {
        for(int i = 1; i < 21; i++)
        {
            for(int j = 1; j < 31; j++)
            {
                save.write((char *)&LevelTable[i][j], sizeof(LevelTable));
            }
        }
        save.close();
    }
    else
    {
        std::cout << "ERROR: Save file cannot open";
        exit(EXIT_FAILURE);
    }
}

void Game::loadMap(std::string game)
{
    std::fstream load;
    load.open(game, std::ios::in);
    if(load.is_open())
    {
        for(int i = 1; i < 21; i++)
        {
            for(int j = 1; j < 31; j++)
            {
                load.read((char *)&LevelTable[i][j], sizeof(LevelTable));
            }
        }
        load.close();
    }
    else
    {
        std::cout << "ERROR: File not found";
        exit(EXIT_FAILURE);
    }
}

void Game::saveData(std::string game)
{
    std::fstream save;
    save.open(game, std::ios::out);
    if(save.is_open())
    {
        save << player.key << std::endl;
        save << player.posx << std::endl;
        save << player.posy << std::endl;
        save << level;
        save.close();
    }
    else
    {
        std::cout << "ERROR: Save file cannot open";
        exit(EXIT_FAILURE);
    }
}

void Game::loadData(std::string game)
{
    std::fstream load;
    load.open(game, std::ios::in);
    if(load.is_open())
    {
        load >> player.key >> player.posx >> player.posy >> level;
        load.close();
    }
    else
    {
        std::cout << "ERROR: File not found";
        exit(EXIT_FAILURE);
    }
}
