#pragma once
#include"Entity.h"
class DynamicEntity: public Entity
{
public:
	DynamicEntity(Position coordinate);
	int getAttack();
	int getHealth();

	/// <summary>
	/// Проводит бой между двумя объектами. Один из них атакующий, другой - защищающийся
	/// </summary
	/// <returns>Если защищающийся объект умер в результате боя, true. Иначе - false</returns>
	bool combat(DynamicEntity& defender);
private:
	int health;
	int attack;
};

