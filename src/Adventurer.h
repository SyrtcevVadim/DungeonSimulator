#pragma once
#include"DynamicEntity.h"
#include<vector>

using std::vector;

class Adventurer : public DynamicEntity
{
public:
	Adventurer(Position pos);

	void setGoal(vector<int> path);
	bool hasGoal();
	int getNextNode();
private:

	/// <summary>
	/// ѕуть к цели
	/// </summary>
	vector<int> path;

	/// <summary>
	/// »ндекс текущей €чейки пути
	/// </summary>
	int currentNodeIndex;

	static const vector<char> SYMBOLS;
	static const Color COLOR;
};