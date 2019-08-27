#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

bool isColliding(Sprite sprite1, Sprite sprite2);

class Enemy
{
    private:
        bool onScreen;
        bool facingRight;

        int xv;
        float yv;
        int yv_acceleration;

        float oldX;
        float oldY;

        Texture* textureRight;
        Texture* textureLeft;
        Sprite sprite;
    public:
        Enemy(Texture* _textureRight, Texture* _textureLeft, bool facingRight);
        Sprite getSprite();
        void update(Time deltaTime, Platform* platforms, int numPlatforms);
};