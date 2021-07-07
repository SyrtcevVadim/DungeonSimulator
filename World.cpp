#include "src/World.h"
#include"lib/rlutil/rlutil.h"

#include<iostream>
#include<string>
#include<random>

using std::cout;
using std::string;
using std::seed_seq;
using std::mt19937;
using std::uniform_int_distribution;


void showMatrix(int** matrix, unsigned int row, unsigned int col)
{
	rlutil::cls();
	for (size_t i{ 0u }; i < row; i++)
	{
		for (size_t j{ 0u }; j < col; j++)
		{
			cout << matrix[i][j];
		}
		cout << '\n';
	}
}

World::World(unsigned int rowNum, unsigned int colNum) :
	ROW_NUMBER(rowNum), COLUMN_NUMBER(colNum)
{
	// Выделяем место под матрицы состояний
	currentFrameBuffer = new char* [ROW_NUMBER];
	nextFrameBuffer = new char* [ROW_NUMBER];

	for (size_t i{ 0u }; i < ROW_NUMBER; i++)
	{
		currentFrameBuffer[i] = new char[COLUMN_NUMBER];
		nextFrameBuffer[i] = new char[COLUMN_NUMBER];
	}
}

void World::generate(string strSeed)
{
	// Создаём ключ-генерации на основе пользовательской строки
	seed_seq seed(strSeed.begin(), strSeed.end());
	mt19937 generator(seed);

	// Задаём распределение(диапазон значений) для нашего генератора
	uniform_int_distribution<int> mapDistribution(0, 1);
	uniform_int_distribution<int> entitiesDistribution();
	int** matrix = new int*[ROW_NUMBER];
	for (size_t i{ 0 }; i < ROW_NUMBER; i++)
	{
		matrix[i] = new int[COLUMN_NUMBER];
	}

	// Задаём начальное условие для клеточного автомата
	for (size_t i{ 0 }; i < ROW_NUMBER; i++)
	{
		for (size_t j{ 0 }; j < COLUMN_NUMBER; j++)
		{
			matrix[i][j] = mapDistribution(generator);
		}
	}
	// Отображаем начальное состояние системы
	showMatrix(matrix, ROW_NUMBER, COLUMN_NUMBER);




	for (size_t i{ 0 }; i < ROW_NUMBER; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;

}

World::~World()
{
	// Удаляем память, выделенную под буферы
	for (size_t i{ 0u }; i < ROW_NUMBER; i++)
	{
		delete[] currentFrameBuffer[i];
		delete[] nextFrameBuffer[i];
	}

	delete[] currentFrameBuffer;
	delete[] nextFrameBuffer;
}