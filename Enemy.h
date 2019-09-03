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
        Texture* textureRight2;
        Texture* textureLeft2;
        Sprite sprite;

        float animationSpeed;
        float timer;

        bool isDead;
    public:
        Enemy(Texture* _textureRight, Texture* _textureLeft, Texture* _textureRight2, Texture* _textureLeft2, int _facingRight);
        Sprite getSprite();
        void update(Time deltaTime, Platform* platforms, int numPlatforms);
        void die();
        bool getIsDead();
        bool canDelete();
};