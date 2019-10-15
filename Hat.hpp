#include "Hat.h"

#include <math.h>

Hat::Hat(Texture* _texture)
{
    texture = _texture;
    sprite.setTexture(*texture);
    onEntity = true;
    yv = 0;
}

Hat::Hat() {}

Sprite Hat::getSprite()
{
    return sprite;
}

Sprite Hat::getDrawableSprite(int scale)
{
    Sprite tempSprite = sprite;
    tempSprite.setPosition(round(sprite.getPosition().x / scale) * scale, round(sprite.getPosition().y / scale) * scale);
    return tempSprite;
}

void Hat::update(Time deltaTime)
{
    //yv += 300 * deltaTime.asSeconds();
}

void Hat::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}