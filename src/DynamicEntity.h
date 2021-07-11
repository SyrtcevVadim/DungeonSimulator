#pragma once
#include"Entity.h"
class DynamicEntity: public Entity
{
public:
	DynamicEntity(Position coordinate);
	int getAttack();
	int getHealth();

	/// <summary>
	/// Устанавливает цель для объекта
	/// </summary>
	/// <param name="path">Путь к цели</param>
	void setGoal(vector<int> path);
	/// <summary>
	/// Проверяет, достиг ли объект цели
	/// </summary>
	bool reachedGoal();
	/// <summary>
	/// Проверяет, есть ли у объекта цель
	/// </summary>
	bool hasGoal();
	/// <summary>
	/// Возвращает номер ячейки, в которую будет совершено перемещение
	/// </summary>
	int getNextNode();

	int getViewRadius();
	int getAttackRadius();

	/// <summary>
	/// Проводит бой между двумя объектами. Один из них атакующий, другой - защищающийся
	/// </summary
	/// <returns>Если защищающийся объект умер в результате боя, true. Иначе - false</returns>
	bool combat(DynamicEntity& defender);
protected:
	/// <summary>
	/// Путь к цели
	/// </summary>
	vector<int> path;
	/// <summary>
	/// Индекс текущей ячейки пути
	/// </summary>
	int currentNodeIndex;

	/// <summary>
	/// Радиус обзора объекта
	/// </summary>
	int viewRadius;
	/// <summary>
	/// Радиус атаки объекта
	/// </summary>
	int attackRadius;
	/// <summary>
	/// Очки здоровья объекта
	/// </summary>
	int health;
	/// <summary>
	/// Очки атаки объекта
	/// </summary>
	int attack;
};

