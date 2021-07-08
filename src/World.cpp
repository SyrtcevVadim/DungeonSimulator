#include "World.h"
#include"../lib/rlutil/rlutil.h"
#include"Utilities.h"


#include<stdio.h>
#include<iostream>
#include<string>
#include<algorithm>
#include<random>

using std::cout;
using std::cin;
using std::string;
using std::find;
using std::seed_seq;
using std::mt19937;
using std::uniform_int_distribution;

map<int, char> World::symbolTable
{
	{0, FLOOR_SYMBOL},
	{1, WALL_SYMBOL},
	{2, TREASURE_SYMBOL}
};

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


bool World::isInBounds(Coordinate coord)
{
	if (0 <= coord.col && coord.col < COLUMN_NUMBER)
	{
		if (0 <= coord.row && coord.row < ROW_NUMBER)
		{
			return true;
		}
	}
	return false;
}

bool World::isAlive(int** matrix, Coordinate coord)
{
	if (matrix[coord.row][coord.col] == 1)
	{
		return true;
	}
	return false;
}

int World::countNeigbourCells(int** matrix, Coordinate coord)
{
	int counter{ 0 };
	Coordinate neighbours[8]
	{
		{ coord.row - 1, coord.col - 1 },	// Левый верхний угол
		{ coord.row - 1, coord.col  },		// Верхний
		{ coord.row - 1, coord.col + 1  },	// Правый верхний угол
		{ coord.row, coord.col - 1  },		// Левый
		{ coord.row, coord.col + 1  },		// Правый
		{ coord.row + 1, coord.col - 1 },	// Левый нижний угол
		{ coord.row + 1, coord.col  },		// Нижний
		{ coord.row + 1, coord.col + 1  }	// Правый нижний угол
	};
	for (Coordinate coord : neighbours)
	{
		if (isInBounds(coord) && isAlive(matrix, coord))
		{
			counter++;
		}
	}
	return counter;
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

void World::addMapBorders(int** matrix)
{
	// Вертикальные границы
	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		matrix[i][0] = matrix[i][COLUMN_NUMBER - 1] = 1;
	}
	// Горизонтальные границы
	for (int i{ 0 }; i < COLUMN_NUMBER; i++)
	{
		matrix[0][i] = matrix[ROW_NUMBER - 1][i] = 1;
	}
}

void World::swapBuffers(int **&a, int **&b)
{
	int** temp = a;
	a = b;
	b = temp;
}

void World::makeMap(int** matrix)
{
	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		for (int j{ 0 }; j < COLUMN_NUMBER; j++)
		{
			currentFrameBuffer[i][j] = symbolTable[matrix[i][j]];
		}
	}
}

void World::drawMap()
{
	rlutil::cls();
	rlutil::hidecursor();
	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		for (int j{ 0 }; j < COLUMN_NUMBER; j++)
		{
			char currentSymbol{ currentFrameBuffer[i][j] };

			if (currentSymbol == WALL_SYMBOL)
			{
				// Окрашиваем стены в тёмно-серый цвет
				rlutil::setColor(Color::GRAY);
			}
			else if (currentSymbol == FLOOR_SYMBOL)
			{
				rlutil::setColor(Color::WHITE);
			}
			cout << currentFrameBuffer[i][j];
		}
		cout << '\n';
	}
	rlutil::resetColor();
	cout << '\n';
}


bool World::areBuffersEqual(int** first, int** second)
{
	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		for (int j{ 0 }; j < COLUMN_NUMBER; j++)
		{
			if (first[i][j] != second[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

void World::startCellularAutomatonGeneration(int **&matrix, initializer_list<int> born, initializer_list<int> save)
{
	// Создаём вспомогательный буфер
	int **secondMatrix = new int*[ROW_NUMBER];
	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		secondMatrix[i] = new int[COLUMN_NUMBER];
	}


	// Запускаем клеточный автомат
	do
	{
		for (int i{ 0 }; i < ROW_NUMBER; i++)
		{
			for (int j{ 0 }; j < COLUMN_NUMBER; j++)
			{
				int currentCellValue{ matrix[i][j] };
				// Количество живых соседей у текущей клетки
				int neighbourCount{ countNeigbourCells(matrix, Coordinate{i,j}) };

				// Если текущая клетка - пол(мёртвая)
				if (currentCellValue == 0)
				{
					// Правило рождения стены
					if (find(born.begin(), born.end(), neighbourCount) != born.end())
					{
						secondMatrix[i][j] = 1;
					}
					else
					{
						// Иначе клетка остаётся полом
						secondMatrix[i][j] = 0;
					}
					
				}
				else if(currentCellValue == 1)
				{
					// Правило сохранения стены
					if (find(save.begin(), save.end(), neighbourCount) != save.end())
					{
						secondMatrix[i][j] = 1;
					}
					else
					{
						// Стена превращается в пол
						secondMatrix[i][j] = 0;
					}
				}
			}
		}
		
		// Меняем буферы местами
		swapBuffers(matrix, secondMatrix);

	} while (!areBuffersEqual(matrix, secondMatrix));
	
	// Освобождаем память
	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		delete[] secondMatrix[i];
	}
	delete[] secondMatrix;
}

void World::generate(string strSeed)
{
	// Создаём ключ-генерации на основе пользовательской строки
	seed_seq seed(strSeed.begin(), strSeed.end());
	mt19937 generator;
	generator.seed(seed);

	// Задаём распределение(диапазон значений) для нашего генератора
	uniform_int_distribution<int> mapDistribution(1, 5);

	int** firstMatrix = new int*[ROW_NUMBER];
	for (size_t i{ 0 }; i < ROW_NUMBER; i++)
	{
		firstMatrix[i] = new int[COLUMN_NUMBER];
	}

	// Задаём начальное условие для клеточного автомата
	for (size_t i{ 0 }; i < ROW_NUMBER; i++)
	{
		for (size_t j{ 0 }; j < COLUMN_NUMBER; j++)
		{
			// Пол появляется в 3-х случаях из 5
			firstMatrix[i][j] = mapDistribution(generator)/4;
		}
	}
	
	// Запускаем клеточный автомат
	startCellularAutomatonGeneration(firstMatrix, { 5,6,7,8 }, { 3, 4,5,6,7,8 });

	// Рисуем границы карты
	addMapBorders(firstMatrix);

	// Делаем карту из матрицы сгенерированных данных
	makeMap(firstMatrix);

	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		delete[] firstMatrix[i];
	}
	delete[] firstMatrix;

}

World::~World()
{
	// Удаляем память, выделенную под буферы
	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		delete[] currentFrameBuffer[i];
		delete[] nextFrameBuffer[i];
	}

	delete[] currentFrameBuffer;
	delete[] nextFrameBuffer;
}