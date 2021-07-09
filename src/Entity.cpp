#include"Entity.h"

Entity::Entity(Coordinate coordinate):
	currentCoordinate(coordinate)
{}

Coordinate Entity::getCoordinate()
{
	return currentCoordinate;
}

void Entity::setColor(Color color)
{
	this->color = color;
}

Color Entity::getColor()
{
	return color;
}


void Entity::setSymbol(char symbol)
{
	this->symbol = symbol;
}


char Entity::getSymbol()
{
	return symbol;
}