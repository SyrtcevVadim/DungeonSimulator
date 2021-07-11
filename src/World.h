#pragma once
#include<string>
#include<map>
#include<list>
#include<vector>
#include<initializer_list>
#include"Utilities.h"

#include"Treasure.h"
#include"Monster.h"
#include"Adventurer.h"

using std::map;
using std::initializer_list;
using std::string;
using std::vector;
using std::list;

class World
{
public:
	World(unsigned int rowNum, unsigned int colNum);
	~World();
	/// <summary>
	/// Процедурно генерирует мир на основе ключа.
	/// </summary>
	void generate();

	/// <summary>
	/// Отрисовывает статическую карту в консоли
	/// </summary>
	void drawMap();



	/// <summary>
	/// Обрабатывает жизненный цикл статических и динамических объектов на карте
	/// </summary>
	void render();


private:
	/// <summary>
	/// Ширина игрового поля
	/// </summary
	const int COLUMN_NUMBER;
	/// <summary>
	/// Высота игрового поля
	/// </summary>
	const int ROW_NUMBER;

	/// <summary>
	/// Список смежности для графа, описывающего сеть ячеек пола, по которым можно передвигаться
	/// </summary>
	vector<list<int>> adjacencyList;

	/// <summary>
	/// Хранит информацию обо всех сокровищах на карте
	/// </summary>
	vector<Treasure> treasures;

	/// <summary>
	/// Хранит информацию обо всех монстрах на карте
	/// </summary>
	vector<Monster> monsters;

	/// <summary>
	/// Хранит информацию обо всех исследователях
	/// </summary>
	vector<Adventurer> adventureres;

	/// <summary>
	/// Производит поиск пути между вершинами startNode и destinationNode с помощью
	/// обхода графа в ширину
	/// </summary>
	/// <param name="startNode">Стартовая вершина</param>
	/// <param name="destinationNode">Конечная вершина</param>
	/// <returns>Путь от стартовой вершины до конечной</returns>
	vector<int>  BFS(int startNode, int destinationNode);

	/// <summary>
	/// Матрица текущего состояния игрового поля
	/// </summary>
	char** playingMap;

	/// <summary>
	/// Рисует клетку карты в позиции pos
	/// </summary>
	/// <param name="pos"></param>
	void drawMapCell(Position pos);

	/// <summary>
	/// Переводит порядковый номер клетки в её координаты
	/// </summary>
	Position numberToPosition(int number);

	/// <summary>
	/// Переводит координаты клетки в её порядковый номер
	/// </summary>
	int positionToNumber(Position position);

	/// <summary>
	/// Создаёт граф на основе сгенерированной карты
	/// </summary>
	void createGraph(int **matrix);

	/// <summary>
	/// Запускает процедурную генерацию пещеры с помощью клеточного автомата.
	/// </summary>
	/// <param name="matrix">Матрица сгенерированной карты</param>
	/// <param name="born">Задёт правила рождения стенок</param>
	/// <param name="save">Задаёт правила сохранения стенок</param>
	void startCellularAutomatonGeneration(int **&matrix, initializer_list<int> born, initializer_list<int> save);

	/// <summary>
	/// Проверяет, одинаковые ли буферы(поэлементно) или нет
	/// </summary>
	bool areBuffersEqual(int** first, int** second);

	/// <summary>
	/// Проверяет, находится ли координата в рамках матрицы
	/// </summary>
	bool isInBounds(Position coord);

	/// <summary>
	/// Подсчитывает количество живых клеток-соседей для клетки с координатами coord
	/// </summary>
	/// <returns>Количество соседей у клетки с координатами coord</returns>
	int countNeigbourCells(int** matrix, Position coord);

	/// <summary>
	/// Проверяет, жива ли клетка по координатам coord
	/// </summary>
	bool isAlive(int** matrix, Position coord);

	/// <summary>
	/// Добавляет на карту граничные стены
	/// </summary>
	/// <param name="matrix"></param>
	void addMapBorders(int** matrix);

	/// <summary>
	/// Меняет два буфера местами
	/// </summary>
	void swapBuffers(int** &a, int** &b);

	/// <summary>
	/// Делает символьную карту на основе сгенерированного буфера чисел
	/// </summary>
	void makeMap(int** matrix);

	/// <summary>
	/// Возвращает случайный номер соседней ячейки для ячейки с координатами pos
	/// </summary>
	int chooseRandomNeighbour(Position pos);

	/// <summary>
	/// Возвращает список соседних ячеек карты в радиусе radius
	/// </summary>
	/// <param name="initial">Координаты ячейки, для которой ищутся все соседние ячейки</param>
	/// <param name="radius">Радиус поиска</param>
	vector<Position> getNeighboursPositions(Position initial, int radius);

	/// <summary>
	/// Сообщает, должен ли двигаться объект или нет
	/// </summary>
	bool haveToMove();

	void move(Monster& object);

	void move(Adventurer& object);
};

