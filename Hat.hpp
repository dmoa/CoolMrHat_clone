#include "Hat.h"

Hat::Hat(Texture* _texture)
{
    texture = _texture;
    sprite.setTexture(*texture);
}

Sprite Hat::getSprite()
{
    return sprite;
}

void Hat::update(Time deltaTime)
{

}

void Hat::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}