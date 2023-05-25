#pragma once
#include "InterfaceObject.h"
class Image : public InterfaceObject
{
public:
	Image(int x, int y, int height, int width, std::string texturePath, std::string textureHoveredPath)
		:InterfaceObject(x, y, height, width, texturePath, textureHoveredPath) {}

	Image(int x, int y, int height, int width, std::string texturePath)
		:InterfaceObject(x, y, height, width, texturePath) {}

	void ballCollisionEffect() {};
};