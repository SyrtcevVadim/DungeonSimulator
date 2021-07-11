#include"DynamicEntity.h"


DynamicEntity::DynamicEntity(Position coordinate) :
	Entity(coordinate), viewRadius(0), health(0), attack(0)
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

void DynamicEntity::setGoal(vector<int> path)
{
	this->path = path;
	currentNodeIndex = 0;
}

bool DynamicEntity::reachedGoal()
{
	if ((path.size() > 0) && (currentNodeIndex == path.size() - 1))
	{
		return true;
	}
	return false;
}

bool DynamicEntity::hasGoal()
{
	if ((path.size() > 0) && (currentNodeIndex < path.size() - 1))
	{
		return true;
	}
	return false;
}

int DynamicEntity::getNextNode()
{
	return path[++currentNodeIndex];
}

int DynamicEntity::getViewRadius()
{
	return viewRadius;
}

int DynamicEntity::getAttackRadius()
{
	return attackRadius;
}