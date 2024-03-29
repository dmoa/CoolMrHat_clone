#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"

using namespace sf;

bool isColliding(Sprite sprite1, Sprite sprite2);

class Player
{
    private:
        Texture* textureRight;
        Texture* textureLeft;
        // right is 1, left is -1
        int direction;
        Sprite sprite;
        int width;
        int height;
        float oldX;
        float oldY;
        float xv;
        float yv;
        float setXV;
        float yv_acceleration;

        std::vector <Hat*> hats;
        
        bool isDead;
    public:
        Player(Texture* _textureRight, Texture* _textureLeft);
        Sprite getSprite();
        Sprite getDrawableSprite(int scale);
        void moveLeft(Time deltaTime);
        void moveRight(Time deltaTime);
        void stopX();
        void jump();
        void die();
        bool getIsDead();
        void update(Time deltatime, Platform* platform, int numPlatforms, std::vector <Enemy> &enemies, std::vector <Hat> &worldHats);
        void addHat(Hat* hat);
        Hat getHat(int index);
        int getNumHats();
};