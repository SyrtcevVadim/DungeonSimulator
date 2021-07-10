#pragma once
#include"StaticEntity.h"
#include"Utilities.h"

#include<vector>

using std::vector;

class Treasure: public StaticEntity
{
public:
	Treasure(Position coord);
private:
	static const vector<char> SYMBOLS;
	static const Color COLOR;
};