#pragma once
#include"StaticEntity.h"
#include"Utilities.h"

#include<vector>

using std::vector;

class Treasure: public StaticEntity
{
public:
	Treasure(Position coord);
	friend bool operator == (const Treasure& lVal, const Treasure& rVal);
private:
	static const vector<char> SYMBOLS;
	static const Color COLOR;
};