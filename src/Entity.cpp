#include"Entity.h"

Entity::Entity(Position coordinate):
	currentCoordinate(coordinate)
{}

Position Entity::getCoordinate()
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