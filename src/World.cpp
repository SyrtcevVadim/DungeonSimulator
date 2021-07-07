#include "World.h"
#include"../lib/rlutil/rlutil.h"
#include"Utilities.h"


#include<stdio.h>
#include<iostream>
#include<string>
#include<random>

using std::cout;
using std::cin;
using std::string;
using std::seed_seq;
using std::mt19937;
using std::uniform_int_distribution;

map<int, char> World::symbolTable
{
	{0, FLOOR_SYMBOL},
	{1, WALL_SYMBOL}
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
		{ coord.row - 1, coord.col - 1 },	// ����� ������� ����
		{ coord.row - 1, coord.col  },		// �������
		{ coord.row - 1, coord.col + 1  },	// ������ ������� ����
		{ coord.row, coord.col - 1  },		// �����
		{ coord.row, coord.col + 1  },		// ������
		{ coord.row + 1, coord.col - 1 },	// ����� ������ ����
		{ coord.row + 1, coord.col  },		// ������
		{ coord.row + 1, coord.col + 1  }	// ������ ������ ����
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
	// �������� ����� ��� ������� ���������
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
	// ������������ �������
	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		matrix[i][0] = matrix[i][COLUMN_NUMBER - 1] = 1;
	}
	// �������������� �������
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
				// ���������� ����� � ����-����� ����
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

void World::generate(string strSeed)
{
	// ������ ����-��������� �� ������ ���������������� ������
	seed_seq seed(strSeed.begin(), strSeed.end());
	mt19937 generator;
	generator.seed(seed);

	// ����� �������������(�������� ��������) ��� ������ ����������
	uniform_int_distribution<int> mapDistribution(1, 5);

	int** firstMatrix = new int*[ROW_NUMBER];
	int** secondMatrix = new int* [ROW_NUMBER];
	for (size_t i{ 0 }; i < ROW_NUMBER; i++)
	{
		firstMatrix[i] = new int[COLUMN_NUMBER];
		secondMatrix[i] = new int[COLUMN_NUMBER];
	}

	// ����� ��������� ������� ��� ���������� ��������
	for (size_t i{ 0 }; i < ROW_NUMBER; i++)
	{
		for (size_t j{ 0 }; j < COLUMN_NUMBER; j++)
		{
			// ��� ���������� � 3-� ������� �� 5
			firstMatrix[i][j] = mapDistribution(generator)/4;
		}
	}
	// ���������� ��������� ��������� �������
	//showMatrix(firstMatrix, ROW_NUMBER, COLUMN_NUMBER);
	//cin.get();
	
	// ������ ���������, ���� � ��� 5,6,7 ��� 8 �������
	// ������ �����������, ���� � ��� 3,4,5,6,7,8 �������
	// ������ �������, ���� � ��� 0, 1 ��� 2 ������
	// B678/S345678
	// ����� ������ - �����(1), ������� - ���(0)
	// ��������� ��������� �������
	for (int k{ 0 }; k < GENERATOR_ITERATIONS; k++)
	{
		for (int i{ 0 }; i < ROW_NUMBER; i++)
		{
			for (int j{ 0 }; j < COLUMN_NUMBER; j++)
			{
				int currentCell{ firstMatrix[i][j] };
				int neighbours{ countNeigbourCells(firstMatrix, Coordinate{i, j}) };
				if (currentCell == 0)
				{
					if (5 <= neighbours && neighbours <= 8)
					{
						// ��� ���������� ������
						secondMatrix[i][j] = 1;
					}
					else
					{
						// ��� ������� �����
						secondMatrix[i][j] = 0;
					}
				}
				if (currentCell == 1)
				{
					if (3 <= neighbours)
					{
						// ����� ������� ������
						secondMatrix[i][j] = 1;
					}
					else
					{
						// ����� ���������� �����
						secondMatrix[i][j] = 0;
					}
				}
			}
		}
		// ������ firstMatrix � secondMatrix �������
		swapBuffers(firstMatrix, secondMatrix);
	}

	// ������ ������� �����
	addMapBorders(firstMatrix);

	// ������ ����� �� ������� ��������������� ������
	makeMap(firstMatrix);

	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		delete[] firstMatrix[i];
		delete[] secondMatrix[i];
	}
	delete[] firstMatrix;
	delete[] secondMatrix;

}

World::~World()
{
	// ������� ������, ���������� ��� ������
	for (size_t i{ 0u }; i < ROW_NUMBER; i++)
	{
		delete[] currentFrameBuffer[i];
		delete[] nextFrameBuffer[i];
	}

	delete[] currentFrameBuffer;
	delete[] nextFrameBuffer;
}