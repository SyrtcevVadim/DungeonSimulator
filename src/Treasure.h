#pragma once
#include"StaticEntity.h"
#include"Utilities.h"

class Treasure: public StaticEntity
{
public:
	Treasure(Coordinate coord, char symbol, Color color, int worth);

	
private:
	/// <summary>
	/// �������� ���������
	/// </summary>
	int worth;
};