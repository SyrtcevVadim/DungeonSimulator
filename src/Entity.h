#pragma once
#include"Utilities.h"

class Entity
{
public:
	Entity(Coordinate coordinate);

	Coordinate getCoordinate();
	Color getColor();
	char getSymbol();
protected:
	// ���������� ������� �� �����
	Coordinate currentCoordinate;
	// ���� �������
	Color color;
	/// <summary>
	/// ������ �������
	/// </summary>
	char symbol;

	void setColor(Color color);
	void setSymbol(char symbol);
};

