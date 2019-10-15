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

        Hat hat;
    public:
        Enemy(Texture* _textureRight, Texture* _textureLeft, Texture* _textureRight2, Texture* _textureLeft2, 
            int _facingRight, Texture* _hatTexture);
        Sprite getSprite();
        Sprite getDrawableSprite(int scale);
        Hat getHat();
        void update(Time deltaTime, Platform* platforms, int numPlatforms);
        void die(std::vector <Hat> &worldHats);
        bool getIsDead();
        bool canDelete();
};