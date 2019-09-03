#include "Enemy.h"
#include <iostream>
// we pass a reference, it holds the memory address, we did this by dereferencing our texture variable in main.cpp
// we do this so we avoid creating a copy of texture, which is what would happen if we just pass in a variable
Enemy::Enemy(Texture* _textureRight, Texture* _textureLeft, Texture* _textureRight2, Texture* _textureLeft2, int _facingRight)
{
    textureRight = _textureRight;
    textureLeft = _textureLeft;
    textureRight2 = _textureRight2;
    textureLeft2 = _textureLeft2;
    //we could just pass *_texture, but like, we did it this way to make it clearer
    // setTexture likes just getting the actual value of texture, so we basically give the actual value, 
    // not the memory address to the function
    // never mind we need to do it this way because we are going to have more than one texture

    onScreen = false;

    facingRight = _facingRight;
    if (facingRight == 1)
    {
        xv = 100;
        sprite.setPosition(-200, 408);
        sprite.setTexture(*textureRight);
    } 
    else 
    {
        xv = -100;
        sprite.setPosition(434, 408);
        sprite.setTexture(*textureLeft);
    }

    yv = 0;
    yv_acceleration = 1000;

    animationSpeed = 0.4;
    timer = animationSpeed;

    isDead = false;
}

Sprite Enemy::getSprite()
{
    return sprite;
}

void Enemy::die()
{
    yv = -400;
    isDead = true;
}

bool Enemy::getIsDead()
{
    return isDead;
}

bool Enemy::canDelete()
{
    return isDead && sprite.getPosition().y > WH;
}

void Enemy::update(Time deltaTime, Platform* platforms, int numPlatforms)
{

    if ((sprite.getPosition().x > 0 && facingRight) || (sprite.getPosition().x < 344 && !facingRight))
    {
        onScreen = true;
    }

    // if onScreen, gravity and collision is enabled
    // while offScreen, we don't want it to fall into the void
    if (onScreen)
    {
        oldY = sprite.getPosition().y;
        oldX = sprite.getPosition().x;

        yv += yv_acceleration * deltaTime.asSeconds();
        sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + yv * deltaTime.asSeconds());
        sprite.setPosition(sprite.getPosition().x + xv * deltaTime.asSeconds(), sprite.getPosition().y);
        
        if (!isDead)
        {
            // yes this is terrible way to do animation
            timer -= deltaTime.asSeconds();
            if (timer < 0)
            {
                timer = animationSpeed;
                if (facingRight)
                {
                    if (sprite.getTexture() == textureRight)
                    {
                        sprite.setTexture(*textureRight2);
                    }
                    else
                    {
                        sprite.setTexture(*textureRight);
                    }
                }
                else
                {
                    if (sprite.getTexture() == textureLeft)
                    {
                        sprite.setTexture(*textureLeft2);
                    }
                    else
                    {
                        sprite.setTexture(*textureLeft);
                    }
                }
            }
            for (int i = 0; i < numPlatforms; i++)
            {
                if (isColliding(sprite, platforms[i].getSprite()) && oldY + sprite.getLocalBounds().height <= platforms[i].getY())
                {
                    sprite.setPosition(sprite.getPosition().x, platforms[i].getY() - sprite.getLocalBounds().height);
                    yv = 0;
                }
                if (isColliding(sprite, platforms[i].getSprite()) && oldX >= platforms[i].getX() + platforms[i].getWidth())
                {
                    sprite.setPosition(platforms[i].getX() + platforms[i].getWidth(), sprite.getPosition().y);
                    xv *= -1;
                    facingRight = true;
                    sprite.setTexture(*textureRight);
                }
                if (isColliding(sprite, platforms[i].getSprite()) && oldX + sprite.getLocalBounds().width <= platforms[i].getX())
                {
                    sprite.setPosition(platforms[i].getX() - sprite.getLocalBounds().width, sprite.getPosition().y);
                    xv *= -1;
                    facingRight = false;
                    sprite.setTexture(*textureLeft);
                }
                if (isColliding(sprite, platforms[i].getSprite()) && oldY >= platforms[i].getY() + platforms[i].getHeight()) 
                {
                    sprite.setPosition(sprite.getPosition().x, platforms[i].getY() + platforms[i].getHeight());
                    yv = 0;
                }
            }
        }
    } 
    else
    {
        sprite.setPosition(sprite.getPosition().x + xv * deltaTime.asSeconds(), sprite.getPosition().y);
    }
}