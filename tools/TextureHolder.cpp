#include "TextureHolder.h"

#include <assert.h>

// lowkey creating an instance, but it's being assigned to the pointer of itself, so it doesn't get a new name
TextureHolder* TextureHolder::instance = nullptr;

TextureHolder::TextureHolder()
{
    // if there is no instance of this class, i.e. null pointer, then we want to assign itself to itself (not confusing at all right?)
    assert(instance == nullptr);
    instance = this;
}

Texture& TextureHolder::getTexture(string const& filename)
{
    // getting the variable "textures", and assigning it to m
    // we use the arrow operator, because instance is a pointer, and we want one value in "instance"
    auto m = instance->textures;
    // find returns key (filename) & value (the actual texture) IF IT EXISTS
    auto keyValuePair = m.find(filename);
    // if keyValuePair DOES NOT EQUAL to out of bounds, i.e. it exists in m
    if (keyValuePair != m.end())
    {
        // then return the value
        // second basically means value
        return keyValuePair->second;
    }
    else
    {
        // IF IT IS OUT BOUNDS, THEN WE CREATE IT IN MAP
        // auto&, figure out the type, but make it a reference
        // we "connecting" texture and m[filename], so, when we do loadFromFile, it's going to add this to m[filename],
        // which is instance->textures
        auto& texture = m[filename]; // key
        texture.loadFromFile(filename); // value
        return texture; 
        // alternative would be to do:
        // m[filename].loadFromFile(filename)
        // value m.find(filename)->second
    }
}