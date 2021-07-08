#include"Entity.h"

Entity::Entity(Coordinate coordinate, char symbol, Color color):
	currentCoordinate(coordinate), symbol(symbol), color(color)
{}

Coordinate Entity::getCoordinate()
{
	return currentCoordinate;
}

Color Entity::getColor()
{
	return color;
}

char Entity::getSymbol()
{
	return symbol;
}