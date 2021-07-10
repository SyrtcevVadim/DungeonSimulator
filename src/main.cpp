#include<iostream>
#include<random>
#include<string>

#include"../lib/rlutil/rlutil.h"
#include"Utilities.h"
#include"Generator.h"
#include"Treasure.h"
#include"Adventurer.h"
#include"World.h"

using std::cout;
using std::cin;
using std::string;
using std::getline;

// ������ ���������� �������
#define SLEEP_TIME_ARG 1
#define MAP_HEIGHT_ARG 2
#define MAP_WIDTH_ARG 3
#define GENERATION_SEED_ARG 4

int main(int argc, char **argv)
{
	if (argc < 5)
	{
		cout << "NOT ENOUGH ARGUMENTS!\n";
		return -1;
	}
	// �������� ���� � �������������
	int turnSleepTime{ atoi(argv[SLEEP_TIME_ARG]) };
	// ������ ����� (���������� �����)
	int mapHeight{ atoi(argv[MAP_HEIGHT_ARG]) };
	// ������ ����� (���������� ��������)
	int mapWidth{ atoi(argv[MAP_WIDTH_ARG]) };
	// ����� ��������� (������ ������������ �����)
	string generationSeed{ argv[GENERATION_SEED_ARG]};

	/*Position f{ 1,2 }, s{ 1,3 }, t{ 1,2 };
	cout << "1,2 == 1,3: " << (f == s) << '\n';
	cout << "1,2 == 1,2: " << (f == t) << '\n';

	Treasure a(f), b(s), c(t);
	cout << "a == b: " << (a == b) << '\n';
	cout << "a == c: " << (a == c) << '\n';
	

	Adventurer x(Position{ 10, 20 }), y(Position{ 55, 11 }), z(Position{ 10, 20 });
	cout << "x == y: " << (x == y) << '\n';
	cout << "x == z: " << (z == x) << '\n';
	cin.get();*/

	Generator::Init(generationSeed);
	World world(mapHeight, mapWidth);
	world.generate();
	// ������ ������ ���� � �������
	world.drawMap();

	// ���� ����������
	while (1)
	{	
		rlutil::msleep(turnSleepTime);
		world.render();
	}

	return 0;
}