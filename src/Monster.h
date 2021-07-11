#pragma once
#include"DynamicEntity.h"
#include"Generator.h"
#include<vector>
#include<list>

using std::list;
using std::vector;

class Monster: public DynamicEntity
{
public:
	Monster(Position coord);

private:
	static const vector<char> SYMBOLS;
	static const Color COLOR;
};