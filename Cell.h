#pragma once

#include "InterfaceObject.h"
#include "Texture.h"

enum Symbol
{
	Circle,
	Cross,
	Empty
};

class Cell : public InterfaceObject
{
public:

	void onClick();

	Cell(int x, int y, int width, int height, Symbol& whoseTurn);
	
	virtual ~Cell();

	void setSymbol(Symbol);

	Symbol getSymbol();

	Texture* getTexture();


private:
	Symbol symbol;
	Symbol& whoseTurn;
	Texture* circleTexture;
	Texture* crossTexture;
	
};

