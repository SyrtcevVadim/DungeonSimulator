#pragma once
#include<string>
#include<map>
#include<list>
#include<initializer_list>
#include"Utilities.h"

#include"Treasure.h"
#include"Monster.h"

using std::map;
using std::initializer_list;
using std::string;
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
	/// Таблица код-объект. Каждому коду соответствует свой символ объекта
	/// </summary>
	static map<int, char> symbolTable;
	/// <summary>
	/// Ширина игрового поля
	/// </summary
	const int COLUMN_NUMBER;
	/// <summary>
	/// Высота игрового поля
	/// </summary>
	const int ROW_NUMBER;

	/// <summary>
	/// Количество итераций цикла генерации карты
	/// </summary>
	const int GENERATOR_ITERATIONS{ 10 };

	/// <summary>
	/// Хранит информацию обо всех сокровищах на карте
	/// </summary>
	list<Treasure> treasures;

	/// <summary>
	/// Хранит информацию обо всех монстрах на карте
	/// </summary>
	list<Monster> monsters;


	/// <summary>
	/// Матрица текущего состояния игрового поля
	/// </summary>
	char** playingMap;


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
	bool isInBounds(Coordinate coord);

	/// <summary>
	/// Подсчитывает количество живых клеток-соседей для клетки с координатами coord
	/// </summary>
	/// <returns>Количество соседей у клетки с координатами coord</returns>
	int countNeigbourCells(int** matrix, Coordinate coord);

	/// <summary>
	/// Проверяет, жива ли клетка по координатам coord
	/// </summary>
	bool isAlive(int** matrix, Coordinate coord);

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
};

