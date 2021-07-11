#pragma once
#include"Entity.h"
class DynamicEntity: public Entity
{
public:
	DynamicEntity(Position coordinate);
	int getAttack();
	int getHealth();

	/// <summary>
	/// ������������� ���� ��� �������
	/// </summary>
	/// <param name="path">���� � ����</param>
	void setGoal(vector<int> path);
	/// <summary>
	/// ���������, ������ �� ������ ����
	/// </summary>
	bool reachedGoal();
	/// <summary>
	/// ���������, ���� �� � ������� ����
	/// </summary>
	bool hasGoal();
	/// <summary>
	/// ���������� ����� ������, � ������� ����� ��������� �����������
	/// </summary>
	int getNextNode();

	int getViewRadius();
	int getAttackRadius();

	/// <summary>
	/// �������� ��� ����� ����� ���������. ���� �� ��� ���������, ������ - ������������
	/// </summary
	/// <returns>���� ������������ ������ ���� � ���������� ���, true. ����� - false</returns>
	bool combat(DynamicEntity& defender);
protected:
	/// <summary>
	/// ���� � ����
	/// </summary>
	vector<int> path;
	/// <summary>
	/// ������ ������� ������ ����
	/// </summary>
	int currentNodeIndex;

	/// <summary>
	/// ������ ������ �������
	/// </summary>
	int viewRadius;
	/// <summary>
	/// ������ ����� �������
	/// </summary>
	int attackRadius;
	/// <summary>
	/// ���� �������� �������
	/// </summary>
	int health;
	/// <summary>
	/// ���� ����� �������
	/// </summary>
	int attack;
};

