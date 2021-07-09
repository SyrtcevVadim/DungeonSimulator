#include "World.h"
#include"../lib/rlutil/rlutil.h"

#include"Utilities.h"
#include"Generator.h"
#include"Treasure.h"

#include<stdio.h>
#include<iostream>
#include<string>
#include<algorithm>
#include<random>

using std::cout;
using std::cin;
using std::string;
using std::find;


map<int, char> World::symbolTable
{
	{0, FLOOR_SYMBOL},
	{1, WALL_SYMBOL},
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
	rlutil::saveDefaultColor();
	// �������� ����� ��� ������� ���������
	playingMap = new char* [ROW_NUMBER];

	for (size_t i{ 0u }; i < ROW_NUMBER; i++)
	{
		playingMap[i] = new char[COLUMN_NUMBER];
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
			playingMap[i][j] = symbolTable[matrix[i][j]];
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
			char currentSymbol{ playingMap[i][j] };

			if (currentSymbol == WALL_SYMBOL)
			{
				// ���������� ����� � ����-����� ����
				rlutil::setColor(Color::GRAY);
			}
			else if (currentSymbol == FLOOR_SYMBOL)
			{
				rlutil::setColor(Color::WHITE);
			}
			cout << playingMap[i][j];
		}
		cout << '\n';
	}
	rlutil::resetColor();
	rlutil::locate(1, ROW_NUMBER + 1);
}

void World::render()
{
	// ������������ ����������� �������
	for (Treasure t : treasures)
	{
		// �������� ����������
		int x{ t.getCoordinate().col };
		int y{ t.getCoordinate().row };
		// ������������� ���������. ���������� 1, ��������� � ������� ���������� ���������� � 1(� � ��� � 0)
		rlutil::locate(x+1, y+1);
		rlutil::setColor(t.getColor());
		cout << t.getSymbol();
	}
	// ������������ ������������ �������
	for (Monster m : monsters)
	{
		int x{ m.getCoordinate().col };
		int y{ m.getCoordinate().row };

		rlutil::locate(x + 1, y + 1);
		rlutil::setColor(m.getColor());
		cout << m.getSymbol();
	}

	rlutil::resetColor();
	rlutil::locate(1, ROW_NUMBER + 1);
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
	// ������ ��������������� �����
	int **secondMatrix = new int*[ROW_NUMBER];
	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		secondMatrix[i] = new int[COLUMN_NUMBER];
	}


	// ��������� ��������� �������
	do
	{
		for (int i{ 0 }; i < ROW_NUMBER; i++)
		{
			for (int j{ 0 }; j < COLUMN_NUMBER; j++)
			{
				int currentCellValue{ matrix[i][j] };
				// ���������� ����� ������� � ������� ������
				int neighbourCount{ countNeigbourCells(matrix, Coordinate{i,j}) };

				// ���� ������� ������ - ���(������)
				if (currentCellValue == 0)
				{
					// ������� �������� �����
					if (find(born.begin(), born.end(), neighbourCount) != born.end())
					{
						secondMatrix[i][j] = 1;
					}
					else
					{
						// ����� ������ ������� �����
						secondMatrix[i][j] = 0;
					}
					
				}
				else if(currentCellValue == 1)
				{
					// ������� ���������� �����
					if (find(save.begin(), save.end(), neighbourCount) != save.end())
					{
						secondMatrix[i][j] = 1;
					}
					else
					{
						// ����� ������������ � ���
						secondMatrix[i][j] = 0;
					}
				}
			}
		}
		
		// ������ ������ �������
		swapBuffers(matrix, secondMatrix);

	} while (!areBuffersEqual(matrix, secondMatrix));
	
	// ����������� ������
	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		delete[] secondMatrix[i];
	}
	delete[] secondMatrix;
}

void World::generate()
{
	int** firstMatrix = new int*[ROW_NUMBER];
	for (size_t i{ 0 }; i < ROW_NUMBER; i++)
	{
		firstMatrix[i] = new int[COLUMN_NUMBER];
	}

	// ����� ��������� ������� ��� ���������� ��������
	for (size_t i{ 0 }; i < ROW_NUMBER; i++)
	{
		for (size_t j{ 0 }; j < COLUMN_NUMBER; j++)
		{
			// ��� ���������� � 3-� ������� �� 5
			firstMatrix[i][j] = Generator::getCell();
		}
	}
	
	// ��������� ��������� �������
	startCellularAutomatonGeneration(firstMatrix, { 5,6,7,8 }, { 3, 4,5,6,7,8 });

	// ������ ������� �����
	addMapBorders(firstMatrix);

	// ������ ����� �� ������� ��������������� ������
	makeMap(firstMatrix);

	// ���������� ����������� � ������������ ������� �� ����
	for (int i{ 1 }; i < ROW_NUMBER-1; i++)
	{
		for (int j{ 1 }; j < COLUMN_NUMBER; j++)
		{
			// ������� ����� ���������� ������ �� ���� ����������
			if (firstMatrix[i][j] == 0)
			{
				if (Generator::getObject() <= TREASURE_APPEAR_PROBABILITY)
				{
					treasures.push_back(Treasure(Coordinate{ i, j }));
				}
				else if (Generator::getObject() <= MONSTER_APPEAR_PROBABILITY)
				{
					monsters.push_back(Monster(Coordinate{ i,j }));
				}
			}
		}
	}


	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		delete[] firstMatrix[i];
	}
	delete[] firstMatrix;

}

World::~World()
{
	// ������� ������, ���������� ��� ������
	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		delete[] playingMap[i];
	}

	delete[] playingMap;
}