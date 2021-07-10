#include"Monster.h"
#include"Utilities.h"

#include<vector>
#include<list>

using std::list;
using std::vector;

const vector<char> Monster::SYMBOLS{ 'm', 'M', '&'};
const Color Monster::COLOR{ Color::RED };

const int Monster::MAX_HEALTH{ 10 };
const int Monster::ATTACK{ 2 };

Monster::Monster(Position coord) :
	DynamicEntity(coord)
{
	setColor(COLOR);
	setSymbol(SYMBOLS[Generator::getNumber(0, SYMBOLS.size() - 1)]);
}

