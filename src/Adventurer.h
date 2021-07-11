#pragma once
#include"DynamicEntity.h"
#include<vector>

using std::vector;

class Adventurer : public DynamicEntity
{
public:
	Adventurer(Position pos);

private:

	static const int MAX_HEALTH;
	static const int ATTACK;
	static const vector<char> SYMBOLS;
	static const Color COLOR;
};