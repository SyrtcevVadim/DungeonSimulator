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

enum  Color
{
	BLACK=0, BLUE=1,GREEN=2, LIGHT_BLUE=3, RED=4,
	PURPLE=5, YELLOW=6, LIGHT_GRAY=7, GRAY=8, ORANGE=12, GOLD=14,
	WHITE=15
};

const int MIN_TREASURE_WORTH{ 1 };
const int MAX_TREASURE_WORTH{ 5 };

// Вероятность появления любого объекта от - значение от 1 до 1'000
// Вероятность появления сокровища на полу
const int TREASURE_APPEAR_PROBABILITY{ 10 };
// Вероятность появления монстра на полу
const int MONSTER_APPEAR_PROBABILITY{ 15 };

const char WALL_SYMBOL{ static_cast<char>(176) };
const char FLOOR_SYMBOL{ '.' };
const char TREASURE_SYMBOL{ '$' };

const char MONSTER_SYMBOL{ 'M' };