#include"Monster.h"
#include"Utilities.h"

const vector<char> Monster::SYMBOLS{ 'm', 'M', '&'};
const Color Monster::COLOR{ Color::RED };

Monster::Monster(Position coord) :
	DynamicEntity(coord)
{
	setColor(COLOR);
	setSymbol(SYMBOLS[Generator::getNumber(0, SYMBOLS.size() - 1)]);
}

void Monster::move()
{
	// Монстры двигаются хаотично в одном из восьми направлений

	// Получаем вектор соседних свободных ячеек
}