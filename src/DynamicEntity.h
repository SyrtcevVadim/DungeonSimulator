#pragma once
#include"Entity.h"
class DynamicEntity: public Entity
{
public:
	DynamicEntity(Coordinate coordinate, char symbol, Color color);
private:
	void move(Coordinate newCoordinate);
};

