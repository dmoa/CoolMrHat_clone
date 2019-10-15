#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Hat 
{
    private:
        Sprite sprite;
        Texture* texture;
    public:
        Hat();
        Hat(Texture* _texture);
        Sprite getSprite();
        Sprite getDrawableSprite(int scale);
        void update(Time deltaTime);
        void setPosition(float x, float y);
};