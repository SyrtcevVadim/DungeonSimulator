#pragma once
#include<string>
#include<map>

using std::map;
using std::string;

class Coordinate
{
public:
	/// <summary>
	/// Номер строки
	/// </summary>
	int row;
	/// <summary>
	/// Номер столбца
	/// </summary>
	int col;
};

class World
{
public:
	World(unsigned int rowNum, unsigned int colNum);
	~World();
	/// <summary>
	/// Процедурно генерирует мир на основе ключа.
	/// </summary>
	/// <param name="strSeed">Ключ генерации</param>
	void generate(string strSeed);

	/// <summary>
	/// Отрисовывает картинку в консоли
	/// </summary>
	void drawMap();


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
	const int GENERATOR_ITERATIONS{ 5 };

	/// <summary>
	/// Матрица текущего состояния игрового поля
	/// </summary>
	char** currentFrameBuffer;

	/// <summary>
	/// Матрица следующего состояний игрового поля
	/// </summary>
	char** nextFrameBuffer;

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

	void drawMapBorders(int** matrix);

	void swapBuffers(int** &a, int** &b);

	/// <summary>
	/// Делает символьную карту на основе сгенерированного буфера чисел
	/// </summary>
	void makeMap(int** matrix);
};

