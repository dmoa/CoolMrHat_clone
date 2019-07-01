#include <SFML/Graphics.hpp>
using namespace sf;

class Platform
{
    private:
        Sprite sprite;
    public:
        Platform();
        int getWidth();
        int getHeight();
        int getX();
        int getY();
        Sprite getSprite();
        void setTexture(Texture* texture);
        void setPosition(int x, int y);
};