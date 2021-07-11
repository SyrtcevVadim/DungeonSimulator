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
	vector<Treasure> treasures;

	/// <summary>
	/// ������ ���������� ��� ���� �������� �� �����
	/// </summary>
	vector<Monster> monsters;

	/// <summary>
	/// ������ ���������� ��� ���� ��������������
	/// </summary>
	vector<Adventurer> adventureres;

	/// <summary>
	/// ���������� ����� ���� ����� ��������� startNode � destinationNode � �������
	/// ������ ����� � ������
	/// </summary>
	/// <param name="startNode">��������� �������</param>
	/// <param name="destinationNode">�������� �������</param>
	/// <returns>���� �� ��������� ������� �� ��������</returns>
	vector<int>  BFS(int startNode, int destinationNode);

	/// <summary>
	/// ������� �������� ��������� �������� ����
	/// </summary>
	char** playingMap;

	/// <summary>
	/// ������ ������ ����� � ������� pos
	/// </summary>
	/// <param name="pos"></param>
	void drawMapCell(Position pos);

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

	/// <summary>
	/// ���������� ��������� ����� �������� ������ ��� ������ � ������������ pos
	/// </summary>
	int chooseRandomNeighbour(Position pos);

	/// <summary>
	/// ���������� ������ �������� ����� ����� � ������� radius
	/// </summary>
	/// <param name="initial">���������� ������, ��� ������� ������ ��� �������� ������</param>
	/// <param name="radius">������ ������</param>
	vector<Position> getNeighboursPositions(Position initial, int radius);

	/// <summary>
	/// ��������, ������ �� ��������� ������ ��� ���
	/// </summary>
	bool haveToMove();

	void move(Monster& object);

	void move(Adventurer& object);
};

