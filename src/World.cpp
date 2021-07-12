#include "World.h"
#include"../lib/rlutil/rlutil.h"

#include<fstream>

#include"Utilities.h"
#include"Generator.h"
#include"Treasure.h"
#include"Adventurer.h"


#include<iostream>
#include<string>
#include<algorithm>
#include<random>
#include<stack>

using std::ofstream;
using std::cout;
using std::cin;
using std::stack;
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


vector<Position> World::getNeighboursPositions(Position initial, int radius)
{
	vector<Position> result;
	for (int row{ initial.row - radius }; row <= (initial.row + radius); row++)
	{
		for (int col{ initial.col - radius }; col <= (initial.col + radius); col++)
		{
			Position current{ row, col };
			if (isInBounds(current) && (current != initial))
			{
				result.push_back(current);
			}
		}
	}
	return result;
}

int World::countNeigbourCells(int** matrix, Position coord)
{
	int counter{ 0 };
	Position neighbours[8]
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
	// Выделяем место под матрицы состояний
	playingMap = new char* [ROW_NUMBER];

	for (size_t i{ 0u }; i < ROW_NUMBER; i++)
	{
		playingMap[i] = new char[COLUMN_NUMBER];
	}
	turnCounter = 0u;
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

void World::drawMapCell(Position pos)
{
	int col{ pos.col };
	int row{ pos.row };
	rlutil::locate(col + 1, row + 1);
	char currentSymbol{ playingMap[row][col] };

	if (find(WALL_SYMBOLS.begin(), WALL_SYMBOLS.end(), currentSymbol) != WALL_SYMBOLS.end())
	{
		// Окрашиваем стены в тёмно-серый цвет
		rlutil::setColor(Color::GRAY);
	}
	else if (find(FLOOR_SYMBOLS.begin(), FLOOR_SYMBOLS.end(), currentSymbol) != FLOOR_SYMBOLS.end())
	{
		rlutil::setColor(Color::WHITE);
	}
	cout << playingMap[row][col];
}

void World::drawMap()
{
	rlutil::cls();
	rlutil::hidecursor();
	// Рисуем карту
	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		for (int j{ 0 }; j < COLUMN_NUMBER; j++)
		{
			drawMapCell(Position{ i, j });
		}
		cout << '\n';
	}
	// Рисуем объекты
	// Обрабатываем статические объекты
	for (Treasure t : treasures)
	{
		// Получаем координаты
		int col{ t.getPosition().col };
		int row{ t.getPosition().row };
		// Позиционируем указатель. Прибавляем 1, поскольку в консоли координаты начинаются с 1(а у нас с 0)
		rlutil::locate(col + 1, row + 1);
		rlutil::setColor(t.getColor());
		cout << t.getSymbol();
	}
	// Обрабатываем динамические объекты
	for (Monster m : monsters)
	{
		int col{ m.getPosition().col };
		int row{ m.getPosition().row };

		// Рисуем объект
		rlutil::locate(col + 1, row + 1);
		rlutil::setColor(m.getColor());
		cout << m.getSymbol();
	}

	for (Adventurer a : adventurers)
	{
		int col{ a.getPosition().col };
		int row{ a.getPosition().row };

		// Рисуем объект
		rlutil::locate(col + 1, row + 1);
		rlutil::setColor(a.getColor());
		cout << a.getSymbol();
	}

	rlutil::resetColor();
	rlutil::locate(1, ROW_NUMBER + 1);
}

void World::showInfo()
{
	rlutil::resetColor();
	// Отображаем информацию о количестве сокровищ
	rlutil::locate(COLUMN_NUMBER + 1, 1);
	cout << "Remaining treasures: " << treasures.size() << "\t\t\t\n";
	// Отображаем информацию о количестве монстров
	rlutil::locate(COLUMN_NUMBER + 1, 2);
	cout << "Monsters: "<<monsters.size() <<'\t';
	int monstersCounters[3]{ 0 };
	for (Monster& m : monsters)
	{
		switch (m.getSymbol())
		{
		case 'm':
			monstersCounters[0]++; break;
		case 'M':
			monstersCounters[1]++; break;
		case '&':
			monstersCounters[2]++; break;
		}
	}
	cout << "m: " << monstersCounters[0] << 
		"\tM: " << monstersCounters[1]  << 
		"\t&: " << monstersCounters[2] << "\t\t\t\n";
	rlutil::locate(COLUMN_NUMBER + 1, 3);
	// Отображаем информацию о количестве людей
	cout << "Adventurers: "<<adventurers.size() <<"\t";
	// Счётчик количества людей типа 'A'
	int adventurersCounters[6]{ 0 };
	for (Adventurer& a : adventurers)
	{
		switch (a.getSymbol())
		{
		case 'A': 
			++adventurersCounters[0]; break;
		case 'B':
			++adventurersCounters[1]; break;
		case 'C':
			++adventurersCounters[2]; break;
		case 'a':
			++adventurersCounters[3]; break;
		case 'b':
			++adventurersCounters[4]; break;
		case 'c':
			++adventurersCounters[5]; break;
		}
	}
	cout << "A: " << adventurersCounters[0] <<
		"\tB: " << adventurersCounters[1] <<
		"\tC: " << adventurersCounters[2] <<
		"\ta: " << adventurersCounters[3] <<
		"\tb: " << adventurersCounters[4] <<
		"\tc: " << adventurersCounters[5] << '\t';
	rlutil::resetColor();
	rlutil::locate(1, ROW_NUMBER + 1);
}

void World::render()
{
	rlutil::hidecursor();
	// Обрабатываем статические объекты
	for (Treasure &t : treasures)
	{
		// Получаем координаты
		int col{ t.getPosition().col };
		int row{ t.getPosition().row };
		// Позиционируем указатель. Прибавляем 1, поскольку в консоли координаты начинаются с 1(а у нас с 0)
		rlutil::locate(col+1, row+1);
		rlutil::setColor(t.getColor());
		cout << t.getSymbol();
	}
	// Обрабатываем динамические объекты
	for (Monster &m : monsters)
	{
		int col{ m.getPosition().col };
		int row{ m.getPosition().row };
		// Стираем старое положение объекта
		rlutil::locate(col + 1, row + 1);
		drawMapCell(m.getPosition());

		// Просчитываем следующую позицию объекта
		move(m);
		col = m.getPosition().col;
		row = m.getPosition().row;
		// Рисуем объект в новой позиции
		rlutil::locate(col + 1, row + 1);
		rlutil::setColor(m.getColor());
		cout << m.getSymbol();

		// Проверяем, может ли монстр кого-нибудь ударить
		for (Position pos : getNeighboursPositions(m.getPosition(), m.getAttackRadius()))
		{
			for (Adventurer& a : adventurers)
			{
				if (pos == a.getPosition())
				{
					// бьём человека!
					rlutil::locate(1, ROW_NUMBER + 1);
					rlutil::resetColor();
					cout << "FIGHT WITH AN ADVENTURER!\t\t\t\n";
					if (m.combat(a))
					{
						// В случае, если человек умер, стираем его с карты
						drawMapCell(a.getPosition());
						// Удаляем его из списка людей
						rlutil::locate(1, ROW_NUMBER + 1);
						rlutil::resetColor();
						cout << "ADVENTURER WAS DEFEATED!\t\t\t\n";
						adventurers.erase(find(adventurers.begin(), adventurers.end(), a));
						break;
					}
				}
			}
		}
	}

	for (Adventurer &a : adventurers)
	{
		// Старые координаты объекта
		int col{ a.getPosition().col };
		int row{ a.getPosition().row };
		// Стираем объект с карты
		rlutil::locate(col + 1, row + 1);
		drawMapCell(a.getPosition());

		move(a);
		// Проверяем, нашёл ли объект сокровище и остались ли они вообще
		if (a.reachedGoal() && !treasures.empty())
		{
			auto res{ treasures.end() };
			for (auto i{ treasures.begin() }; i != treasures.end(); i++)
			{
				if (i->getPosition() == a.getPosition())
				{
					res = i;
				}
			}
			// Если сокровище было найдено
			if (res != treasures.end())
			{
				// Удаляем объект с карты
				drawMapCell(res->getPosition());
				// Удаляем объект из списка
				treasures.erase(res);
			}
		}

		// Новые координаты объекта
		col = a.getPosition().col;
		row = a.getPosition().row;
		// Рисуем объект в новой позиции
		rlutil::locate(col + 1, row + 1);
		rlutil::setColor(a.getColor());
		cout << a.getSymbol();

		// Проверяем, может ли человек кого-нибудь ударить
		for (Position pos : getNeighboursPositions(a.getPosition(), a.getAttackRadius()))
		{
			for (Monster& m : monsters)
			{
				if (pos == m.getPosition())
				{
					// бьём монстра!
					rlutil::resetColor();
					rlutil::locate(1, ROW_NUMBER + 1);
					cout << "FIGHT WITH A MONSTER!\t\t\t\n";
					if (a.combat(m))
					{
						// В случае, если монстр умер, стираем его с карты
						drawMapCell(a.getPosition());
						// Удаляем его из списка монстров
						monsters.erase(find(monsters.begin(), monsters.end(), m));
						rlutil::resetColor();
						rlutil::locate(1, ROW_NUMBER + 1);
						cout << "MONSTER WAS SLAIN BY "<< a.getSymbol() << "!\t\t\t\n";
						break;
					}
				}
			}
		}
	}

	// Отображаем информационное поле в правой части экрана
	showInfo();
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
				int neighbourCount{ countNeigbourCells(matrix, Position{i,j}) };

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
	// Выделяем память под все ячейки карты
	adjacencyList.resize(COLUMN_NUMBER * ROW_NUMBER);

	// Выведем результат в файл
	ofstream fOut("GRAPHINFO.txt");
	

	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		for (int j{ 0 }; j < COLUMN_NUMBER; j++)
		{
			Position currentPos{ i,j };
			int currentNumber{positionToNumber(currentPos)};
			fOut << "(" << currentPos.row << ","<<currentPos.col << ")->" << currentNumber << '\n';
			// Если клетка проходимая - пол
			if (matrix[i][j] == 0)
			{
				// Ищем соседние клетки, по которым можно пройти(пол)
				Position neighbours[8]
				{
					{ currentPos.row - 1, currentPos.col - 1 },		// Левый верхний угол
					{ currentPos.row - 1, currentPos.col  },		// Верхний
					{ currentPos.row - 1, currentPos.col + 1  },	// Правый верхний угол
					{ currentPos.row, currentPos.col - 1  },		// Левый
					{ currentPos.row, currentPos.col + 1  },		// Правый
					{ currentPos.row + 1, currentPos.col - 1 },		// Левый нижний угол
					{ currentPos.row + 1, currentPos.col  },		// Нижний
					{ currentPos.row + 1, currentPos.col + 1  }		// Правый нижний угол
				};
				for (Position pos : neighbours)
				{
					// Если в соседнюю клетку можно пройти, добавляем ее в список смежности текущей ячейки
					if (isInBounds(pos) && matrix[pos.row][pos.col] == 0)
					{
						// Номер ячейки
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

	// Задаём начальное условие для клеточного автомата
	for (size_t i{ 0 }; i < ROW_NUMBER; i++)
	{
		for (size_t j{ 0 }; j < COLUMN_NUMBER; j++)
		{
			// Пол появляется в 3-х случаях из 5
			firstMatrix[i][j] = Generator::getCell();
		}
	}
	
	// Запускаем клеточный автомат
	startCellularAutomatonGeneration(firstMatrix, { 5,6,7,8 }, { 3, 4,5,6,7,8 });

	// Рисуем границы карты
	addMapBorders(firstMatrix);

	// Создаём граф для перемещения объектов
	createGraph(firstMatrix);

	// Делаем карту из матрицы сгенерированных данных
	makeMap(firstMatrix);

	// Генерируем статические и динамические объекты на полу
	for (int i{ 1 }; i < ROW_NUMBER-1; i++)
	{
		for (int j{ 1 }; j < COLUMN_NUMBER; j++)
		{
			// Объекты могут появляться только на полу подземелья
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
				else if (Generator::getObject() <= ADVENTURER_APPER_PROBABILITY)
				{
					adventurers.push_back(Adventurer(Position{ i, j }));
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

vector<int> World::BFS(int startNode, int destinationNode)
{
	// Хранит информацию о том, из какой вершины мы попали в данную.
	// Пригодится для восстановления пути
	vector<int> previous;
	// Показывает, какая вершина уже хранится в стеке
	vector<bool> inStack;
	// Хранит информацию о том, какие вершины были посещены
	vector<bool> visited;

	int size{ ROW_NUMBER * COLUMN_NUMBER };
	previous.resize(size); inStack.resize(size); visited.resize(size);
	// Инициализируем массивы начальными значениями
	for (int i{ 0 }; i < size; i++)
	{
		previous[i] = -1;
		inStack[i] = false;
		visited[i] = false;
	}

	// Стек, в котором хранятся вершины, которые надо посетить
	stack<int> queue;
	queue.push(startNode);
	inStack[startNode] = true;
	while (!queue.empty())
	{
		// Вытаскиваем из стека очередную вершину
		int currentNode{ queue.top() }; queue.pop();
		if (currentNode == destinationNode)
		{
			// Если мы дошли до конечной вершины, то заканчиваем поиск пути
			break;
		}
		// Отмечаем, что мы ее посетили
		visited[currentNode] = true;
		// Отмечаем, что она больше не в стеке
		inStack[currentNode] = false;
		// Добавляем в стек все соседние вершины
		for (int neighbour : adjacencyList[currentNode])
		{
			// Если вершина еще не посещена и она не находится в стеке
			if (!visited[neighbour] && !inStack[neighbour])
			{
				// Запоминаем предыдущую вершину
				previous[neighbour] = currentNode;
				// Закидываем в стек
				queue.push(neighbour);
				// Запоминаем, что данная вершина в стеке
				inStack[neighbour] = true;
			}
		}
	}
	// Пытаемся построить путь до конечной вершины
	vector<int> res;

	// Если до конечной вершины реально добраться из изначальной
	if(previous[destinationNode]!=-1)
	{
		// Строим путь до начальной вершины
		res.push_back(destinationNode);
		int prevNode = previous[destinationNode];
		while (prevNode != -1)
		{
			res.push_back(prevNode);
			prevNode = previous[prevNode];
		}
		std::reverse(res.begin(), res.end());
	}
	return res;
}

int World::chooseRandomNeighbour(Position pos)
{
	// Номер ячейки, в которой находится объект
	int number{ positionToNumber(pos) };
	// Получаем количество соседей для текущей ячейки
	int neighbourNumber{ static_cast<int>(adjacencyList[number].size()) };
	// Вычисляем индекс ячейки, в которую будет двигаться объект
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
	return nextCellNumber;
}

bool World::haveToMove()
{
	return Generator::getBool();
}

void World::move(Monster& object)
{
	// Проверяем, будет ли монстр перемещаться в этот ход
	if (!haveToMove())
	{
		return;
	}

	// Показывает, ходил ли монстр в этот ход или нет
	bool moved{ false };
	// Ищем соперника монстру
	// Проверяем соседние клетки
	for (Position pos : getNeighboursPositions(object.getPosition(), object.getViewRadius()))
	{
		// Проверяем, нет ли в радиусе обзора монстра противника
		for (Adventurer& a : adventurers)
		{
			if (pos == a.getPosition())
			{
				// Устанавливаем монстру цель
				vector<int> path = BFS(positionToNumber(object.getPosition()),
					positionToNumber(pos));
				// Двигаем монстра к цели
				if (path.size() > 0)
				{
					object.setPosition(numberToPosition(path[1]));
					moved = true;
					break;
				}	
			}
		}
	}

	if(!moved)
	{
		// Перемещаем монстра в случайном направлении
		object.setPosition(numberToPosition(chooseRandomNeighbour(object.getPosition())));
	}
}

void World::move(Adventurer& object)
{
	// Проверяем, будет ли герой перемещаться в этот ход
	if (!haveToMove())
	{
		return;
	}

	if (!object.hasGoal() || object.reachedGoal())
	{
		// Пути от человека ко всем сокровищам
		vector<vector<int>> paths;

		for (Treasure t : treasures)
		{
			// Строим путь от человека до сокровища
			paths.push_back(BFS(positionToNumber(object.getPosition()),
								positionToNumber(t.getPosition())));
		}

		int resultPathIndex{ -1 };
		// Выбираем кратчайший путь
		int minLength{ ROW_NUMBER*COLUMN_NUMBER };
		for (int i{ 0 }; i < paths.size(); i++)
		{
			if (paths[i].size() != 0 && paths[i].size() < minLength)
			{
				minLength = paths[i].size();
				resultPathIndex = i;
			}
		}

		if (resultPathIndex == -1)
		{
			// Проверяем, будет ли монстр перемещаться в этот ход
			if (!haveToMove())
			{
				return;
			}
			
			// Перемещаем объект в случайном направлении
			object.setPosition(numberToPosition(chooseRandomNeighbour(object.getPosition())));
		}
		else
		{
			// Устанавливаем путь объекту
			object.setGoal(paths[resultPathIndex]);
		}
	}
	else
	{
		int nextNodeNumber = object.getNextNode();
		// Перемещаем объект
		object.setPosition(numberToPosition(nextNodeNumber));
	}
}

World::~World()
{
	// Удаляем память, выделенную под буферы
	for (int i{ 0 }; i < ROW_NUMBER; i++)
	{
		delete[] playingMap[i];
	}

	delete[] playingMap;
}