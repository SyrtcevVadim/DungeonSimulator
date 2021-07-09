#pragma once
#include"Utilities.h"

class Entity
{
public:
	Entity(Position coordinate);

	void setPosition(Position coordinate);
	Position getPosition();
	Color getColor();
	char getSymbol();
protected:
	// Координаты объетка на карте
	Position currentCoordinate;
	// Цвет объекта
	Color color;
	/// <summary>
	/// Символ объекта
	/// </summary>
	char symbol;

	void setColor(Color color);
	void setSymbol(char symbol);
};

