#pragma once
#include"Entity.h"
class DynamicEntity: public Entity
{
public:
	DynamicEntity(Coordinate coordinate);
private:
	void move(Coordinate newCoordinate);
};

