#include"Adventurer.h"
#include"Generator.h"

const vector<char> Adventurer::SYMBOLS{ 'A','B','C', 'a','b','c'};
const Color Adventurer::COLOR{ Color::GREEN };


Adventurer::Adventurer(Position pos) :
	DynamicEntity(pos)
{
	char symbol{ SYMBOLS[Generator::getNumber(0, SYMBOLS.size() - 1)] };
	setSymbol(symbol);
	setColor(COLOR);
}
