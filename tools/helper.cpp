#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

#include <cstdlib>
#include <ctime>
#include <iostream>


// AABB collision
bool isColliding(Sprite sprite1, Sprite sprite2)
{
    return sprite2.getPosition().x + sprite2.getLocalBounds().width > sprite1.getPosition().x
        && sprite2.getPosition().x < sprite1.getPosition().x + sprite1.getLocalBounds().width
        && sprite2.getPosition().y + sprite2.getLocalBounds().height > sprite1.getPosition().y
        && sprite2.getPosition().y < sprite1.getPosition().y + sprite1.getLocalBounds().height;
}

void generatePlatforms(int smallPlatformSize, int numFloorTiles, int numPlatforms, Texture platformTextures[], int numPlatformTextures, Platform platforms[])
{
    
    srand(time(0));
    for (int i = 0; i < (numPlatforms - numFloorTiles) / 4; i++)
    {
        //platforms[i].setColor();
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
}

// Enemy generateEnemies()
// {

// }