#pragma once
#include<vector>

using std::vector;

class Coordinate
{
public:
	/// <summary>
	/// ����� ������
	/// </summary>
	int row;
	/// <summary>
	/// ����� �������
	/// </summary>
	int col;
};

enum  Color
{
	BLACK=0, BLUE=1,GREEN=2, LIGHT_BLUE=3, RED=4,
	PURPLE=5, YELLOW=6, LIGHT_GRAY=7, GRAY=8, ORANGE=12, GOLD=14,
	WHITE=15
};

// ����������� ��������� ������ ������� �� - �������� �� 1 �� 1'000
// ����������� ��������� ��������� �� ����
const int TREASURE_APPEAR_PROBABILITY{ 10 };
// ����������� ��������� ������� �� ����
const int MONSTER_APPEAR_PROBABILITY{ 15 };

const vector<char> FLOOR_SYMBOLS{ '.',',','`','"','^'};
const vector<char> WALL_SYMBOLS{ static_cast<char>(176), static_cast<char>(177), static_cast<char>(178) };