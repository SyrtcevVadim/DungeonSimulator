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

int Generator::getCell()
{
	// 0 - пол. Появляется в 3-х случаях из 5
	// 1 - стена. Повляется в 2-х случаях из 5
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