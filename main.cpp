#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

#include <typeinfo>
#include <iostream>

#include <SFML/Graphics.hpp>
using namespace sf;

const int WW = 384;
const int WH = 800;


#include "Platform.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

#include "helper.cpp"

int main() {
    RenderWindow window(VideoMode(WW, WH), "Cool Mr Hat Clone");
    window.setVerticalSyncEnabled(true);

    Texture playerTextureRight;
    playerTextureRight.loadFromFile("imgs/playerRight.png");

    window.setIcon(playerTextureRight.getSize().x, playerTextureRight.getSize().y,
                    playerTextureRight.copyToImage().getPixelsPtr());

    Texture playerTextureLeft;
    playerTextureLeft.loadFromFile("imgs/playerLeft.png");
    Player player(&playerTextureRight, &playerTextureLeft);

    Texture enemyTextureRight;
    enemyTextureRight.loadFromFile("imgs/enemyRight.png");
    Texture enemyTextureLeft;
    enemyTextureLeft.loadFromFile("imgs/enemyLeft.png");
    Texture enemyTextureRight2;
    enemyTextureRight2.loadFromFile("imgs/enemyRight2.png");
    Texture enemyTextureLeft2;
    enemyTextureLeft2.loadFromFile("imgs/enemyLeft2.png");

    std::vector <Enemy> enemies;
    enemies.push_back(Enemy (&enemyTextureRight, &enemyTextureLeft, &enemyTextureRight2, &enemyTextureLeft2, true));
    float enemySpawnF = 2;
    float enemySpawnTimer = enemySpawnF;

    const int numPlatformTextures = 3;
    Texture platformTextures[numPlatformTextures];
    for (int i = 0; i < numPlatformTextures; i++)
    {
        platformTextures[i].loadFromFile("imgs/tile" + std::to_string(i + 1) + ".png");
    }

    const int smallPlatformSize = 32;
    const int numFloorTiles = 10;
    const int numPlatforms = 54;
    Platform platforms[numPlatforms];
    generatePlatforms(smallPlatformSize, numFloorTiles, numPlatforms, platformTextures, numPlatformTextures, platforms);

    Clock clock;

    bool rightKeyDown = false;
    bool leftKeyDown = false;
    bool jumpKeyDown = false;

    while (window.isOpen())
    {

        Time deltaTime = clock.restart();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Key::Escape)
                {
                    window.close();
                }
                if (event.key.code == Keyboard::Key::Right)
                {
                    rightKeyDown = true;
                }     
                if (event.key.code == Keyboard::Key::Left)
                {
                    leftKeyDown = true;
                }
                if (event.key.code == Keyboard::Key::Space)
                {
                    jumpKeyDown = true;
                }
            }
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Key::Right)
                {
                    rightKeyDown = false;
                }     
                if (event.key.code == Keyboard::Key::Left)
                {
                    leftKeyDown = false;
                }
                if (event.key.code == Keyboard::Key::Space)
                {
                    jumpKeyDown = false;
                }
            }
        }

        if (!player.getIsDead())
        {
            if (rightKeyDown)
            {
                player.moveRight(deltaTime);
            }
            if (leftKeyDown)
            {
                player.moveLeft(deltaTime);
            }
            if ((!rightKeyDown && !leftKeyDown) || (rightKeyDown && leftKeyDown))
            {
                player.stopX();
            }
            if (jumpKeyDown)
            {
                player.jump();
            }
        }


        player.update(deltaTime, platforms, numPlatforms, enemies);

        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].update(deltaTime, platforms, numPlatforms);
        }
        enemySpawnTimer -= deltaTime.asSeconds();
        if (enemySpawnTimer < 0)
        {
            enemySpawnTimer = enemySpawnF;
            srand(time(0));
            int direction = rand() % 2;
            enemies.push_back(Enemy (&enemyTextureRight, &enemyTextureLeft, &enemyTextureRight2, &enemyTextureLeft2, direction));
        }

        for (int i = 0; i < enemies.size(); i++)
        {
            if (enemies[i].canDelete())
            {
                enemies.erase(enemies.begin() + i);
            }
        }
    
        window.clear();
        window.draw(player.getSprite());
        for (int i = 0; i < numPlatforms; i++)
        {
            window.draw(platforms[i].getSprite());
        }
        for (int i = 0; i < enemies.size(); i++)
        {
            window.draw(enemies[i].getSprite());
        }
        window.display();
    }

    return 0;
}