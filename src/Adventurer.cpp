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

	// Изначально у искателя нет цели
	currentNodeIndex = 0;
}

bool operator==(const Adventurer& lVal, const Adventurer& rVal)
{
	if (lVal.symbol == rVal.symbol &&
		lVal.currentCoordinate == rVal.currentCoordinate)
	{
		return true;
	}
	return false;
}

bool Adventurer::hasGoal()
{
	if (currentNodeIndex <= path.size()-1 && path.size() != 0)
	{
		return true;
	}

	return false;
}

bool Adventurer::reachedGoal()
{
	if (currentNodeIndex == path.size() - 1)
	{
		return true;
	}
	return false;
}

void Adventurer::setGoal(vector<int> path)
{
	this->path = path;
	currentNodeIndex = 0;
}

int Adventurer::getNextNode()
{
	return path[++currentNodeIndex];
}