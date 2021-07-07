#include"Entity.h"

Entity::Entity(Coordinate coordinate):
	currentCoordinate(coordinate)
{}

Coordinate Entity::getCoordinate()
{
	return currentCoordinate;
}

Color Entity::getColor()
{
	return color;
}