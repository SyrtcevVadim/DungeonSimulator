#include"Entity.h"

unsigned int Entity::counter{ 0 };

bool operator==(const Entity& lVal, const Entity& rVal)
{
	if (lVal._hashValue == rVal._hashValue)
	{
		return true;
	}
	return false;
}

Entity::Entity(Position coordinate):
	currentCoordinate(coordinate)
{
	++counter;
	_hashValue = counter;
}

void Entity::setPosition(Position coordinate)
{
	currentCoordinate.col = coordinate.col;
	currentCoordinate.row = coordinate.row;
}

Position Entity::getPosition()
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