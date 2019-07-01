#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Player
{
private:
    Texture* textureRight;
    Texture* textureLeft;
    // right is 1, left is -1
    int direction;
    Sprite sprite;
    float width;
    float height;
    float oldX;
    float oldY;
    float xv;
    float yv;
    float setXV;
    float yv_acceleration;
    bool isColliding(Platform platform);
public:
    Player(Texture* _textureRight, Texture* _textureLeft);
    Sprite getSprite();
    void moveLeft(Time deltaTime);
    void moveRight(Time deltaTime);
    void stopX();
    void jump(Time deltaTime);
    void update(Time deltatime, Platform* platform, int numPlatforms);
};