#pragma once
#include<string>
#include<map>
#include"Utilities.h"

using std::map;
using std::string;

class World
{
public:
	World(unsigned int rowNum, unsigned int colNum);
	~World();
	/// <summary>
	/// ���������� ���������� ��� �� ������ �����.
	/// </summary>
	/// <param name="strSeed">���� ���������</param>
	void generate(string strSeed);

	/// <summary>
	/// ������������ �������� � �������
	/// </summary>
	void drawMap();


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
	/// ������� �������� ��������� �������� ����
	/// </summary>
	char** currentFrameBuffer;

	/// <summary>
	/// ������� ���������� ��������� �������� ����
	/// </summary>
	char** nextFrameBuffer;

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

	void addMapBorders(int** matrix);

	void swapBuffers(int** &a, int** &b);

	/// <summary>
	/// ������ ���������� ����� �� ������ ���������������� ������ �����
	/// </summary>
	void makeMap(int** matrix);
};

