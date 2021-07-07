#pragma once
class Coordinate
{
public:
	/// <summary>
	/// Номер строки
	/// </summary>
	int row;
	/// <summary>
	/// Номер столбца
	/// </summary>
	int col;
};

enum Color
{
	BLACK=0, BLUE=1,GREEN=2, LIGHT_BLUE=3, RED=4,
	PURPLE=5, YELLOW=6, WHITE=7, GRAY=8, ORANGE=12, GOLD=14
};