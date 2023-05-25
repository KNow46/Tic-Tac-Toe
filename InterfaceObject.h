#pragma once
#include "GameObject.h"
#include <functional>
class InterfaceObject : public GameObject
{
public:
	InterfaceObject(int x, int y, int height, int width, std::string texturePath, std::string textureHoveredPath)
		:GameObject(x, y, height, width, texturePath),  isHovered(0), hoverTexture(new Texture(textureHoveredPath)) {};
	InterfaceObject(int x, int y, int height, int width, std::string texturePath)
		:GameObject(x, y, height, width, texturePath), isHovered(0), hoverTexture(new Texture(texturePath)) {};

	virtual void onClick() {};
	void ballCollisionEffect() {};
	
	void setIsHovered(bool isHovered)
	{
		this->isHovered = isHovered;
	}
	virtual Texture* getTexture()
	{ 
		if (isHovered == false)
			return texture;
		else
			return hoverTexture;
	};
protected:
	//bool isVisible;
	bool isHovered;
	Texture* hoverTexture;
};