#pragma once
#include"Utilities.h"

class Entity
{
public:
	Entity(Position coordinate);

	Position getCoordinate();
	Color getColor();
	char getSymbol();
protected:
	// ���������� ������� �� �����
	Position currentCoordinate;
	// ���� �������
	Color color;
	/// <summary>
	/// ������ �������
	/// </summary>
	char symbol;

	void setColor(Color color);
	void setSymbol(char symbol);
};

