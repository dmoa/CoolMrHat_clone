#pragma once

#include <SFML/Graphics.hpp>
#include <map>


using namespace sf;
using namespace std;

class TextureHolder 
{
    private:
        map <string, Texture> textures;
        // static because we don't want to create an instance with a special name, we just want to create a variable called instance, this variable instance, is private unless
        // you call a function, e.g. TextureHolder::getTexture();
        static TextureHolder* instance;
    public:
        TextureHolder();
        static Texture& getTexture(string const& filename);
};