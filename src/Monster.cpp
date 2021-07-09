#include"Monster.h"
#include"Utilities.h"

const vector<char> Monster::SYMBOLS{ 'm', 'M', '&'};
const Color Monster::COLOR{ Color::RED };

Monster::Monster(Coordinate coord) :
	DynamicEntity(coord)
{
	setColor(COLOR);
	setSymbol(SYMBOLS[Generator::getNumber(0, SYMBOLS.size() - 1)]);
}