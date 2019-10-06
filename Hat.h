#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Hat 
{
    private:
        Sprite sprite;
        Texture* texture;
    public:
        Hat(Texture* _texture);
        Sprite getSprite();
        void update(Time deltaTime);
        void setPosition(float x, float y);
};