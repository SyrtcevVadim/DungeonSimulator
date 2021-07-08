#include"Treasure.h"
#include"StaticEntity.h"

Treasure::Treasure(Coordinate coord, char symbol) :
	StaticEntity(coord, symbol, Color::GOLD)
{}

