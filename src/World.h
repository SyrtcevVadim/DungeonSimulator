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
	/// ���������� ���������� ��� �� ������ �����.
	/// </summary>
	void generate();

	/// <summary>
	/// ������������ ����������� ����� � �������
	/// </summary>
	void drawMap();



	/// <summary>
	/// ������������ ��������� ���� ����������� � ������������ �������� �� �����
	/// </summary>
	void render();


private:
	/// <summary>
	/// ������� ���-������. ������� ���� ������������� ���� ������ �������
	/// </summary>
	static map<int, char> symbolTable;
	/// <summary>
	/// ������ �������� ����
	/// </summary
	const int COLUMN_NUMBER;
	/// <summary>
	/// ������ �������� ����
	/// </summary>
	const int ROW_NUMBER;

	/// <summary>
	/// ���������� �������� ����� ��������� �����
	/// </summary>
	const int GENERATOR_ITERATIONS{ 10 };

	/// <summary>
	/// ������ ���������� ��� ���� ���������� �� �����
	/// </summary>
	list<Treasure> treasures;

	/// <summary>
	/// ������ ���������� ��� ���� �������� �� �����
	/// </summary>
	list<Monster> monsters;


	/// <summary>
	/// ������� �������� ��������� �������� ����
	/// </summary>
	char** playingMap;


	/// <summary>
	/// ��������� ����������� ��������� ������ � ������� ���������� ��������.
	/// </summary>
	/// <param name="matrix">������� ��������������� �����</param>
	/// <param name="born">���� ������� �������� ������</param>
	/// <param name="save">����� ������� ���������� ������</param>
	void startCellularAutomatonGeneration(int **&matrix, initializer_list<int> born, initializer_list<int> save);

	/// <summary>
	/// ���������, ���������� �� ������(�����������) ��� ���
	/// </summary>
	bool areBuffersEqual(int** first, int** second);

	/// <summary>
	/// ���������, ��������� �� ���������� � ������ �������
	/// </summary>
	bool isInBounds(Coordinate coord);

	/// <summary>
	/// ������������ ���������� ����� ������-������� ��� ������ � ������������ coord
	/// </summary>
	/// <returns>���������� ������� � ������ � ������������ coord</returns>
	int countNeigbourCells(int** matrix, Coordinate coord);

	/// <summary>
	/// ���������, ���� �� ������ �� ����������� coord
	/// </summary>
	bool isAlive(int** matrix, Coordinate coord);

	/// <summary>
	/// ��������� �� ����� ��������� �����
	/// </summary>
	/// <param name="matrix"></param>
	void addMapBorders(int** matrix);

	/// <summary>
	/// ������ ��� ������ �������
	/// </summary>
	void swapBuffers(int** &a, int** &b);

	/// <summary>
	/// ������ ���������� ����� �� ������ ���������������� ������ �����
	/// </summary>
	void makeMap(int** matrix);
};

