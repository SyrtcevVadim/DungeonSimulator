#pragma once
#include"Utilities.h"

class Entity
{
public:
	Entity(Position coordinate);
	/// <summary>
	/// ������������� ���������� �������
	/// </summary>
	void setPosition(Position coordinate);
	/// <summary>
	/// ���������� ���������� �������
	/// </summary>
	Position getPosition();
	/// <summary>
	/// ���������� ���� �������
	/// </summary>
	Color getColor();
	/// <summary>
	/// ���������� ������ �������
	/// </summary>
	char getSymbol();

	friend bool operator ==(const Entity& lVal, const Entity& rVal);
protected:
	/// <summary>
	/// ������� ��������
	/// </summary>
	static unsigned int counter;

	/// <summary>
	/// ���-�����, ����������� �������� ���� ������ �� �������
	/// </summary>
	unsigned int _hashValue;
	/// <summary>
	/// ���������� ������� �� �����
	/// </summary>
	Position currentCoordinate;
	/// <summary>
	/// ���� �������
	/// </summary>
	Color color;
	/// <summary>
	/// ������ �������
	/// </summary>
	char symbol;

	void setColor(Color color);
	void setSymbol(char symbol);
};

