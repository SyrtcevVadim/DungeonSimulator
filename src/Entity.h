#pragma once
#include"Utilities.h"

class Entity
{
public:
	Entity(Coordinate coordinate);

	Coordinate getCoordinate();
	Color getColor();
protected:
	// ���������� ������� �� �����
	Coordinate currentCoordinate;
	// ���� �������
	Color color;

};

