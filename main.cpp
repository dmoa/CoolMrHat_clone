#include <string>
#include <cstdlib>
#include <ctime>

#include <typeinfo>
#include <iostream>

#include <SFML/Graphics.hpp>
using namespace sf;

const int WW = 394;
const int WH = 800;

#include "Platform.hpp"
#include "Player.hpp"

int main() {
    RenderWindow window(VideoMode(WW, WH), "Cool Mr Hat Clone");
    window.setVerticalSyncEnabled(true);

    Texture playerTextureRight;
    playerTextureRight.loadFromFile("imgs/playerRight.png");
    Texture playerTextureLeft;
    playerTextureLeft.loadFromFile("imgs/playerLeft.png");
    Player player(&playerTextureRight, &playerTextureLeft);
    
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
    for (int i = 0; i < (numPlatforms - numFloorTiles) / 4; i++)
    {
        platforms[i].setTexture(&(platformTextures[rand() % numPlatformTextures]));
        platforms[i].setPosition(0, i * smallPlatformSize);
    }
    for (int i = (numPlatforms - numFloorTiles) / 4; i < (numPlatforms - numFloorTiles) / 2; i++)
    {
        platforms[i].setTexture(&(platformTextures[rand() % numPlatformTextures]));
        platforms[i].setPosition(0,(i + 3) * smallPlatformSize);
    }


    for (int i = (numPlatforms - numFloorTiles) / 2; i < (numPlatforms - numFloorTiles) / 4 * 3; i++)
    {
        platforms[i].setTexture(&(platformTextures[rand() % numPlatformTextures]));
        platforms[i].setPosition(WW - smallPlatformSize, (i - (numPlatforms - numFloorTiles) / 2) * smallPlatformSize);
    }
    for (int i = (numPlatforms - numFloorTiles) / 4 * 3; i < (numPlatforms - numFloorTiles); i++)
    {
        platforms[i].setTexture(&(platformTextures[rand() % numPlatformTextures]));
        platforms[i].setPosition(WW - smallPlatformSize, (i+ 3 - (numPlatforms - numFloorTiles) / 2) * smallPlatformSize);
    }

    for (int i = 44; i < numPlatforms; i++)
    {
        platforms[i].setTexture(&(platformTextures[rand() % numPlatformTextures]));
        platforms[i].setPosition((i - 44 + 1) * smallPlatformSize, WH - smallPlatformSize);
    }

    Clock clock;

    bool rightKeyDown = false;
    bool leftKeyDown = false;

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
                    player.jump(deltaTime);
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
            }
        }



        if (rightKeyDown)
        {
            player.moveRight(deltaTime);
        }
        if (leftKeyDown)
        {
            player.moveLeft(deltaTime);
        }

        player.update(deltaTime, platforms, numPlatforms);


        window.clear();
        window.draw(player.getSprite());
        for (int i = 0; i < numPlatforms; i++)
        {
            window.draw(platforms[i].getSprite());
        }
        window.display();
    }
    return 0;
}