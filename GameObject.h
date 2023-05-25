#pragma once
#include <string>
#include <iostream>
#include "Texture.h"

class GameObject
{
public:
    GameObject(int x, int y, int width, int height, std::string texturePath)
        :x(x), y(y), height(height), width(width), texture(new Texture(texturePath)), isDestroyed(false) {};

    ~GameObject() { delete texture; };

    inline int getHeight() { return height; };

    inline int getWidth() { return width; };

    inline int getX() { return x; };

    inline int getY() { return y; };

    inline void setX(float x) { this->x = x; };

    inline void setY(float y) { this->y = y; };

    inline bool getIsDestroyed() { return isDestroyed; };

    virtual const Texture* getTexture() { return texture; };

protected:
    bool isDestroyed;
    int height;
    int width;
    Texture* texture;
   // int graphicLayerImportance; //for example 0 - background
    double x;
    double y;


};
