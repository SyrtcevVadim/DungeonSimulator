#pragma once
#include<random>
#include<string>

using std::string;
using std::mt19937;
using std::uniform_int_distribution;

class Generator
{
public:
	/// <summary>
	/// Инициализирует ГПСЧ с помощью строкового ключа
	/// </summary>
	/// <param name="strSeed">Строковой ключ-генерирования</param>
	static void Init(string strSeed);

	static int getCell();
	static int getObject();

	/// <summary>
	/// Возвращает ПСЧ из отрезка [min, max]
	/// </summary>
	static int getNumber(int min, int max);

private:
	static mt19937 generator;

	static uniform_int_distribution<> cellDistribution;
	static uniform_int_distribution<> objectsDistribution;
};

