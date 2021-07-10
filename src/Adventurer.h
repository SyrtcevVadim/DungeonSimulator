#pragma once
#include"DynamicEntity.h"
#include<vector>

using std::vector;

class Adventurer : public DynamicEntity
{
public:
	Adventurer(Position pos);

	/// <summary>
	/// Устанавливает цель для искателя
	/// </summary>
	/// <param name="path">Путь к цели</param>
	void setGoal(vector<int> path);
	/// <summary>
	/// Проверяет, достиг ли искатель сокровища или нет
	/// </summary>
	bool reachedGoal();
	/// <summary>
	/// Проверяет, есть ли у искателя цель
	/// </summary>
	bool hasGoal();
	/// <summary>
	/// Возвращает номер ячейки, в которую пойдёт искатель в следующий ход
	/// </summary>
	int getNextNode();

private:

	static const int MAX_HEALTH;
	static const int ATTACK;

	/// <summary>
	/// Путь к цели
	/// </summary>
	vector<int> path;

	/// <summary>
	/// Индекс текущей ячейки пути
	/// </summary>
	int currentNodeIndex;

	static const vector<char> SYMBOLS;
	static const Color COLOR;
};