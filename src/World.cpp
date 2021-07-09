#include "World.h"
#include"../lib/rlutil/rlutil.h"

#include<fstream>

#include"Utilities.h"
#include"Generator.h"
#include"Treasure.h"


#include<iostream>
#include<string>
#include<algorithm>
#include<random>

using std::ofstream;
using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::find;

bool World::isInBounds(Position coord)
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

bool World::isAlive(int** matrix, Position coord)
{
	if (matrix[coord.row][coord.col] == 1)
	{
		return true;
	}
	return false;
}


int World::countNeigbourCells(int** matrix, Position coord)
{
	int counter{ 0 };
	Position neighbours[8]
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
	for (Position coord : neighbours)
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
			int currentCell = matrix[i][j];
			if (currentCell == 0)
			{
				playingMap[i][j] = FLOOR_SYMBOLS[Generator::getNumber(0, FLOOR_SYMBOLS.size() - 1)];
			}
			else
			{
				playingMap[i][j] = WALL_SYMBOLS[Generator::getNumber(0, WALL_SYMBOLS.size() - 1)];
			}
			
		}
	}
}

void World::drawMap()
{
	rlutil::cls();
	rlutil::hidecursor();
	// ������ �����
	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		for (int j{ 0 }; j < COLUMN_NUMBER; j++)
		{
			char currentSymbol{ playingMap[i][j] };

			if (find(WALL_SYMBOLS.begin(), WALL_SYMBOLS.end(), currentSymbol) != WALL_SYMBOLS.end())
			{
				// ���������� ����� � ����-����� ����
				rlutil::setColor(Color::GRAY);
			}
			else if (find(FLOOR_SYMBOLS.begin(), FLOOR_SYMBOLS.end(), currentSymbol) != FLOOR_SYMBOLS.end())
			{
				rlutil::setColor(Color::WHITE);
			}
			cout << playingMap[i][j];
		}
		cout << '\n';
	}
	// ������ �������
	// ������������ ����������� �������
	for (Treasure t : treasures)
	{
		// �������� ����������
		int col{ t.getPosition().col };
		int row{ t.getPosition().row };
		// ������������� ���������. ���������� 1, ��������� � ������� ���������� ���������� � 1(� � ��� � 0)
		rlutil::locate(col + 1, row + 1);
		rlutil::setColor(t.getColor());
		cout << t.getSymbol();
	}
	// ������������ ������������ �������
	for (Monster m : monsters)
	{
		int col{ m.getPosition().col };
		int row{ m.getPosition().row };

		// ������ ������
		rlutil::locate(col + 1, row + 1);
		rlutil::setColor(m.getColor());
		cout << m.getSymbol();
	}

	rlutil::resetColor();
	rlutil::locate(1, ROW_NUMBER + 1);
}

void World::render()
{
	// ������������ ����������� �������
	for (Treasure &t : treasures)
	{
		// �������� ����������
		int col{ t.getPosition().col };
		int row{ t.getPosition().row };
		// ������������� ���������. ���������� 1, ��������� � ������� ���������� ���������� � 1(� � ��� � 0)
		rlutil::locate(col+1, row+1);
		rlutil::setColor(t.getColor());
		cout << t.getSymbol();
	}
	// ������������ ������������ �������
	for (Monster &m : monsters)
	{
		int col{ m.getPosition().col };
		int row{ m.getPosition().row };
		// ������� ������ ��������� �������
		rlutil::locate(col + 1, row + 1);
		char currentSymbol{ playingMap[row][col] };

		if (find(WALL_SYMBOLS.begin(), WALL_SYMBOLS.end(), currentSymbol) != WALL_SYMBOLS.end())
		{
			// ���������� ����� � ����-����� ����
			rlutil::setColor(Color::GRAY);
		}
		else if (find(FLOOR_SYMBOLS.begin(), FLOOR_SYMBOLS.end(), currentSymbol) != FLOOR_SYMBOLS.end())
		{
			rlutil::setColor(Color::WHITE);
		}
		cout << playingMap[row][col];

		// ������������ ��������� ������� �������
		move(m);
		col = m.getPosition().col;
		row = m.getPosition().row;
		// ������ ������ � ����� �������
		rlutil::locate(col + 1, row + 1);
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
				int neighbourCount{ countNeigbourCells(matrix, Position{i,j}) };

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

int World::positionToNumber(Position pos)
{
	return pos.row * COLUMN_NUMBER + pos.col;
}

Position World::numberToPosition(int number)
{
	Position result;
	result.row = number / COLUMN_NUMBER;
	result.col = number % COLUMN_NUMBER;
	return result;
}

void World::createGraph(int **matrix)
{
	// �������� ������ ��� ��� ������ �����
	adjacencyList.resize(COLUMN_NUMBER * ROW_NUMBER);

	// ������� ��������� � ����
	ofstream fOut("GRAPHINFO.txt");
	

	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		for (int j{ 0 }; j < COLUMN_NUMBER; j++)
		{
			Position currentPos{ i,j };
			int currentNumber{positionToNumber(currentPos)};
			fOut << "(" << currentPos.row << ","<<currentPos.col << ")->" << currentNumber << '\n';
			// ���� ������ ���������� - ���
			if (matrix[i][j] == 0)
			{
				// ���� �������� ������, �� ������� ����� ������(���)
				Position neighbours[8]
				{
					{ currentPos.row - 1, currentPos.col - 1 },		// ����� ������� ����
					{ currentPos.row - 1, currentPos.col  },		// �������
					{ currentPos.row - 1, currentPos.col + 1  },	// ������ ������� ����
					{ currentPos.row, currentPos.col - 1  },		// �����
					{ currentPos.row, currentPos.col + 1  },		// ������
					{ currentPos.row + 1, currentPos.col - 1 },		// ����� ������ ����
					{ currentPos.row + 1, currentPos.col  },		// ������
					{ currentPos.row + 1, currentPos.col + 1  }		// ������ ������ ����
				};
				for (Position pos : neighbours)
				{
					// ���� � �������� ������ ����� ������, ��������� �� � ������ ��������� ������� ������
					if (isInBounds(pos) && matrix[pos.row][pos.col] == 0)
					{
						// ����� ������
						int neighbourNum{positionToNumber(pos)};
						adjacencyList[currentNumber].push_back(neighbourNum);
					}
				}
			}
		}
	}
	for (int i{ 0 }; i < adjacencyList.size(); i++)
	{
		fOut << i << ": ";
		for (int neighbour : adjacencyList[i])
		{
			fOut << neighbour << ", ";
		}
		fOut << '\n';
	}
	fOut.close();
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

	// ������ ���� ��� ����������� ��������
	createGraph(firstMatrix);

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
					treasures.push_back(Treasure(Position{ i, j }));
				}
				else if (Generator::getObject() <= MONSTER_APPEAR_PROBABILITY)
				{
					monsters.push_back(Monster(Position{ i,j }));
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

void World::move(Monster& object)
{
	// ����� ������, � ������� ��������� ������
	int number{ positionToNumber(object.getPosition()) };
	// �������� ���������� ������� ��� ������� ������
	int neighbourNumber{ static_cast<int>(adjacencyList[number].size()) };
	// ��������� ������ ������, � ������� ����� ��������� ������
	int nextCellIndex{ Generator::getNumber(0, neighbourNumber - 1) };
	int nextCellNumber{ 0 };
	int counter{ 0 };
	for (int n : adjacencyList[number])
	{
		if (counter == nextCellIndex)
		{
			nextCellNumber = n;
			break;
		}
		counter++;
	}
	// ���������� ������
	rlutil::locate(1, ROW_NUMBER + 1);
	cout << number << ", " << nextCellNumber << "      ";
	object.setPosition(numberToPosition(nextCellNumber));
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