#pragma once
#include"Entity.h"
class DynamicEntity: public Entity
{
public:
	DynamicEntity(Position coordinate);
private:
	virtual void move()=0;
};

