#include"Treasure.h"
#include"Generator.h"


const vector<char> Treasure::SYMBOLS{ '$', '=', '?' };
const Color Treasure::COLOR{ Color::GOLD };

Treasure::Treasure(Position coord) :
	StaticEntity(coord)
{
	setColor(COLOR);
	setSymbol(SYMBOLS[Generator::getNumber(0, SYMBOLS.size()-1)]);
}

