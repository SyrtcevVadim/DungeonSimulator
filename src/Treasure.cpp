#include"Treasure.h"
#include"StaticEntity.h"

Treasure::Treasure(Coordinate coord, char symbol, Color color, int worth) :
	StaticEntity(coord, symbol, color)
{
	this->worth = worth;
}

