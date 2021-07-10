#include"Adventurer.h"
#include"Generator.h"

const vector<char> Adventurer::SYMBOLS{ 'A','B','C', 'a','b','c'};
const Color Adventurer::COLOR{ Color::GREEN };

const int Adventurer::MAX_HEALTH{ 20 };
const int Adventurer::ATTACK{ 5 };

Adventurer::Adventurer(Position pos) :
	DynamicEntity(pos)
{
	char symbol{ SYMBOLS[Generator::getNumber(0, SYMBOLS.size() - 1)] };
	setSymbol(symbol);
	setColor(COLOR);

	// ���������� � �������� ��� ����
	currentNodeIndex = 0;
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