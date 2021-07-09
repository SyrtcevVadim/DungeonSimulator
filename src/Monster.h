#pragma once

#include"DynamicEntity.h"
#include"Generator.h"
#include<vector>

using std::vector;

class Monster: public DynamicEntity
{
public:
	Monster(Position coord);

	virtual void move();

private:
	static const vector<char> SYMBOLS;
	static const Color COLOR;
};