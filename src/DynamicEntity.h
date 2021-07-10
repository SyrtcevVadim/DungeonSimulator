#pragma once
#include"Entity.h"
class DynamicEntity: public Entity
{
public:
	DynamicEntity(Position coordinate);
	int getAttack();
	int getHealth();

	/// <summary>
	/// �������� ��� ����� ����� ���������. ���� �� ��� ���������, ������ - ������������
	/// </summary
	/// <returns>���� ������������ ������ ���� � ���������� ���, true. ����� - false</returns>
	bool combat(DynamicEntity& defender);
private:
	int health;
	int attack;
};

