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
	/// ���� � ����
	/// </summary>
	vector<int> path;

	/// <summary>
	/// ������ ������� ������ ����
	/// </summary>
	int currentNodeIndex;

	static const vector<char> SYMBOLS;
	static const Color COLOR;
};