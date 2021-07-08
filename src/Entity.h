#pragma once
#include"Utilities.h"

class Entity
{
public:
	Entity(Coordinate coordinate, char symbol, Color color);

	Coordinate getCoordinate();
	Color getColor();
protected:
	// ���������� ������� �� �����
	Coordinate currentCoordinate;
	// ���� �������
	Color color;
	/// <summary>
	/// ������ �������
	/// </summary>
	char symbol;
};

