#pragma once
#include"Utilities.h"

class Entity
{
public:
	Entity(Coordinate coordinate, char symbol, Color color);

	Coordinate getCoordinate();
	Color getColor();
protected:
	// Координаты объетка на карте
	Coordinate currentCoordinate;
	// Цвет объекта
	Color color;
	/// <summary>
	/// Символ объекта
	/// </summary>
	char symbol;
};

