#include "Player.h"
//#include <iostream>

Player::Player(Texture* _textureRight, sf::Texture* _textureLeft)
{    
    textureRight = _textureRight;
    textureLeft = _textureLeft;
    direction = 1;
    sprite.setTexture(*textureRight);
    sprite.setPosition(200, 100);

    width = sprite.getLocalBounds().width;
    height = sprite.getLocalBounds().height;

    xv = 0;
    setXV = 400;

    yv = 0;
    oldY = sprite.getPosition().y;
    yv_acceleration = 1000;
}

Sprite Player::getSprite() 
{
    return sprite;
}

void Player::moveLeft(Time deltaTime) 
{
    xv = - setXV;
    if (direction == 1)
    {
        direction = -1;
        sprite.setTexture(*textureLeft);
    }
}

void Player::moveRight(Time deltaTime) 
{
    xv = setXV;
    if (direction == -1)
    {
        direction = 1;
        sprite.setTexture(*textureRight);
    }
}

void Player::stopX()
{
    xv = 0;
}

void Player::jump()
{
    if (yv == 0)
    {
        yv = -400;
    }
}

void Player::update(Time deltaTime, Platform* platforms, int numPlatforms)
{
    oldY = sprite.getPosition().y;
    oldX = sprite.getPosition().x;

    sprite.setPosition(sprite.getPosition().x + xv * deltaTime.asSeconds(), sprite.getPosition().y);
    yv += yv_acceleration * deltaTime.asSeconds();
    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + yv * deltaTime.asSeconds());

    if (sprite.getPosition().y + height > WH)
    {
        yv = 0;
        sprite.setPosition(sprite.getPosition().x, WH - height);
    }
    if (sprite.getPosition().x + width > WW)
    {
        sprite.setPosition(WW - width, sprite.getPosition().y);
    }
    if (sprite.getPosition().x < 0)
    {
        sprite.setPosition(0, sprite.getPosition().y);
    }

    for (int i = 0; i < numPlatforms; i++)
    {
        if (isColliding(sprite, platforms[i].getSprite()) && oldY + height <= platforms[i].getY())
        {
            sprite.setPosition(sprite.getPosition().x, platforms[i].getY() - height);
            yv = 0;
        }
        if (isColliding(sprite, platforms[i].getSprite()) && oldX >= platforms[i].getX() + platforms[i].getWidth())
        {
            sprite.setPosition(platforms[i].getX() + platforms[i].getWidth(), sprite.getPosition().y);
        }
        if (isColliding(sprite, platforms[i].getSprite()) && oldX + width <= platforms[i].getX())
        {
            sprite.setPosition(platforms[i].getX() - width, sprite.getPosition().y);
        }
        if (isColliding(sprite, platforms[i].getSprite()) && oldY >= platforms[i].getY() + platforms[i].getHeight()) 
        {
            sprite.setPosition(sprite.getPosition().x, platforms[i].getY() + platforms[i].getHeight());
            yv = 0;
        }
    }

}