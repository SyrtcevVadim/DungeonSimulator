#include"DynamicEntity.h"
DynamicEntity::DynamicEntity(Coordinate coordinate):
	Entity(coordinate)
{}

void DynamicEntity::move(Coordinate coordinate)
{
	currentCoordinate = coordinate;
}