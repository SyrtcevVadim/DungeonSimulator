#pragma once
#include"DynamicEntity.h"
#include<vector>

using std::vector;

class Adventurer : public DynamicEntity
{
public:
	Adventurer(Position pos);

	/// <summary>
	/// ������������� ���� ��� ��������
	/// </summary>
	/// <param name="path">���� � ����</param>
	void setGoal(vector<int> path);
	/// <summary>
	/// ���������, ������ �� �������� ��������� ��� ���
	/// </summary>
	bool reachedGoal();
	/// <summary>
	/// ���������, ���� �� � �������� ����
	/// </summary>
	bool hasGoal();
	/// <summary>
	/// ���������� ����� ������, � ������� ����� �������� � ��������� ���
	/// </summary>
	int getNextNode();

private:

	static const int MAX_HEALTH;
	static const int ATTACK;

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