#include "Platform.h"

Platform::Platform() {}


void Platform::setTexture(Texture* texture)
{
    sprite.setTexture(*texture);
}

void Platform::setPosition(int x, int y)
{
    sprite.setPosition(x, y);
}

int Platform::getWidth()
{
    return sprite.getLocalBounds().width;
}

int Platform::getHeight()
{
    return sprite.getLocalBounds().height;
}

int Platform::getX()
{
    return sprite.getPosition().x;
}

int Platform::getY()
{
    return sprite.getPosition().y;
}

Sprite Platform::getSprite()
{
    return sprite;
}