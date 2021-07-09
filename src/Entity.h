#pragma once
#include"Utilities.h"

class Entity
{
public:
	Entity(Coordinate coordinate);

	Coordinate getCoordinate();
	Color getColor();
	char getSymbol();
protected:
	// Координаты объетка на карте
	Coordinate currentCoordinate;
	// Цвет объекта
	Color color;
	/// <summary>
	/// Символ объекта
	/// </summary>
	char symbol;

	void setColor(Color color);
	void setSymbol(char symbol);
};

