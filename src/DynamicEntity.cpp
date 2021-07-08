#include"DynamicEntity.h"
DynamicEntity::DynamicEntity(Coordinate coordinate,char symbol, Color color):
	Entity(coordinate, symbol, color)
{}

void DynamicEntity::move(Coordinate coordinate)
{
	currentCoordinate = coordinate;
}