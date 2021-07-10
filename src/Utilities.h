#pragma once
#include<vector>
#include<map>

using std::vector;
using std::map;

class Position
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

	friend bool operator==(const Position& lVal, const Position& rVal);

};


enum  Color
{
	BLACK=0, BLUE=1,GREEN=2, LIGHT_BLUE=3, RED=4,
	PURPLE=5, YELLOW=6, LIGHT_GRAY=7, GRAY=8, ORANGE=12, GOLD=14,
	WHITE=15
};

// Вероятность появления любого объекта от - значение от 1 до 1'000
// Вероятность появления сокровища на полу
const int TREASURE_APPEAR_PROBABILITY{ 20 };
// Вероятность появления монстра на полу
const int MONSTER_APPEAR_PROBABILITY{ 5 };

const int ADVENTURER_APPER_PROBABILITY{ 5 };

const vector<char> FLOOR_SYMBOLS{ '.',',','`','"','^'};
const vector<char> WALL_SYMBOLS{ static_cast<char>(176), static_cast<char>(177), static_cast<char>(178) };