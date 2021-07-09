#pragma once
#include<string>
#include<map>
#include<list>
#include<vector>
#include<initializer_list>
#include"Utilities.h"

#include"Treasure.h"
#include"Monster.h"

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
	/// ������ �������� ����
	/// </summary
	const int COLUMN_NUMBER;
	/// <summary>
	/// ������ �������� ����
	/// </summary>
	const int ROW_NUMBER;

	/// <summary>
	/// ������ ��������� ��� �����, ������������ ���� ����� ����, �� ������� ����� �������������
	/// </summary>
	vector<list<int>> adjacencyList;

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
	/// ��������� ���������� ����� ������ � � ����������
	/// </summary>
	Position numberToPosition(int number);

	/// <summary>
	/// ��������� ���������� ������ � � ���������� �����
	/// </summary>
	int positionToNumber(Position position);

	/// <summary>
	/// ������ ���� �� ������ ��������������� �����
	/// </summary>
	void createGraph(int **matrix);

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
	bool isInBounds(Position coord);

	/// <summary>
	/// ������������ ���������� ����� ������-������� ��� ������ � ������������ coord
	/// </summary>
	/// <returns>���������� ������� � ������ � ������������ coord</returns>
	int countNeigbourCells(int** matrix, Position coord);

	/// <summary>
	/// ���������, ���� �� ������ �� ����������� coord
	/// </summary>
	bool isAlive(int** matrix, Position coord);

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

	void move(Monster& object);
};

