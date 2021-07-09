#include<iostream>
#include<random>
#include<string>

#include"Generator.h"
#include"World.h"

using std::cout;
using std::cin;
using std::string;
using std::getline;



int main()
{
	string userSeed;
	cout << "Please, enter a seed: ";
	getline(cin, userSeed);

	Generator::Init(userSeed);
	World world(100, 200);
	world.generate();
	// Рисуем статическую карту в консоли
	world.drawMap();
	// Отображаем статические и динамические объекты
	world.render();

	return 0;
}