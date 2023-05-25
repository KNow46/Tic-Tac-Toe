#pragma once
#include "InterfaceObject.h"
#include "Texture.h"
class Cell : public InterfaceObject
{
public:
	Cell(int x, int y, int width, int height);

	enum Symbol
	{
		Circle,
		Cross,
		Empty
	};

	void setSymbol(Symbol);

	Symbol getSymbol();

	Texture* getTexture();


private:
	Symbol symbol;
	Texture* CircleTexture;
	Texture* CrossTexture;
	
};

