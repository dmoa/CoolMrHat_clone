#include <string>
#include <cstdlib>
#include <ctime>

#include <typeinfo>
#include <iostream>

#include <SFML/Graphics.hpp>
using namespace sf;

const int WW = 384;
const int WH = 800;


#include "Platform.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

// AABB collision
bool isColliding(Sprite sprite1, Sprite sprite2)
{
    //std::cout << sprite.getPosition().x << std::endl;
    return sprite2.getPosition().x + sprite2.getLocalBounds().width > sprite1.getPosition().x
        && sprite2.getPosition().x < sprite1.getPosition().x + sprite1.getLocalBounds().width
        && sprite2.getPosition().y + sprite2.getLocalBounds().height > sprite1.getPosition().y
        && sprite2.getPosition().y < sprite1.getPosition().y + sprite1.getLocalBounds().height;
}

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
    Enemy enemy(&enemyTextureRight, &enemyTextureLeft, true);
    
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

    srand(time(0));
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



        if (rightKeyDown)
        {
            player.moveRight(deltaTime);
        }
        if (leftKeyDown)
        {
            player.moveLeft(deltaTime);
        }
        if (!rightKeyDown && !leftKeyDown)
        {
            player.stopX();
        }
        if (jumpKeyDown)
        {
            player.jump();
        }

        player.update(deltaTime, platforms, numPlatforms);
        enemy.update(deltaTime, platforms, numPlatforms);


        window.clear();
        window.draw(player.getSprite());
        for (int i = 0; i < numPlatforms; i++)
        {
            window.draw(platforms[i].getSprite());
        }
        window.draw(enemy.getSprite());
        window.display();
    }

    return 0;
}