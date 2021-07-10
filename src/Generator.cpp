#include "Generator.h"

using std::seed_seq;

mt19937 Generator::generator;
uniform_int_distribution<> Generator::cellDistribution(1,5);
uniform_int_distribution<> Generator::objectsDistribution(1, 1'000);


void Generator::Init(string strSeed)
{
	seed_seq seed(strSeed.begin(), strSeed.end());
	generator.seed(seed);
}


bool Generator::getBool()
{
	uniform_int_distribution<> boolDist(0, 1);
	if (boolDist(generator) == 1)
	{
		return true;
	}
	return false;
}

int Generator::getCell()
{
	// 0 - ���. ���������� � 3-� ������� �� 5
	// 1 - �����. ��������� � 2-� ������� �� 5
	return cellDistribution(generator)/4;
}

int Generator::getObject()
{
	return objectsDistribution(generator);
}

int Generator::getNumber(int min, int max)
{
	uniform_int_distribution<> dist(min, max);

	return dist(generator);
}