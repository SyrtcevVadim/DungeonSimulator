#include"Monster.h"
#include"Utilities.h"

#include<vector>
#include<list>

using std::list;
using std::vector;

const vector<char> Monster::SYMBOLS{ 'm', 'M', '&'};
const Color Monster::COLOR{ Color::RED };


Monster::Monster(Position coord) :
	DynamicEntity(coord)
{
	setColor(COLOR);
	setSymbol(SYMBOLS[Generator::getNumber(0, SYMBOLS.size() - 1)]);
	// Устанавливаем характеристики
	health = 10;
	attack = 4;
	viewRadius = 3;
	attackRadius = 1;
	// Изначально у монстра нет никакой цели
	currentNodeIndex = 0;
}

