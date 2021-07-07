#pragma once
#include"Utilities.h"

class Entity
{
public:
	Entity(Coordinate coordinate);

	Coordinate getCoordinate();
	Color getColor();
protected:
	// Координаты объетка на карте
	Coordinate currentCoordinate;
	// Цвет объекта
	Color color;

};

