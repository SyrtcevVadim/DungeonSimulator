#include"DynamicEntity.h"


DynamicEntity::DynamicEntity(Position coordinate):
	Entity(coordinate)
{}

int DynamicEntity::getAttack()
{
	return attack;
}

int DynamicEntity::getHealth()
{
	return health;
}

bool DynamicEntity::combat(DynamicEntity& defender)
{
	int damage{ attack };
	defender.health -= damage;
	if (defender.health <= 0)
	{
		return true;
	}
	return false;
}