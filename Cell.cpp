#pragma once

#include "Cell.h"

Cell::Cell(int x, int y, int width, int height, Symbol & whoseTurn)
	: InterfaceObject(x, y, width, height, "res/textures/empty.png"), symbol(Symbol::Empty), circleTexture(nullptr), crossTexture(nullptr), whoseTurn(whoseTurn)
{
	circleTexture = new Texture("res/textures/circle.png");
	crossTexture = new Texture("res/textures/cross.png");
}

Cell::~Cell()
{	
	delete circleTexture;
	delete crossTexture;
}

void Cell::onClick()
{
	if (symbol == Symbol::Empty)
	{
		symbol = whoseTurn;

		if (whoseTurn == Symbol::Circle)
		{
			whoseTurn = Symbol::Cross;
		}
		else
		{
			whoseTurn = Symbol::Circle;
		}
	}
}

void Cell::setSymbol(Symbol symbol)
{
	this->symbol = symbol;
}

Symbol Cell::getSymbol()
{
	return symbol;
}

Texture* Cell::getTexture()
{
	if (symbol == Symbol::Circle)
		return circleTexture;
	else if (symbol == Symbol::Cross)
		return crossTexture;
	else
		return texture;
}