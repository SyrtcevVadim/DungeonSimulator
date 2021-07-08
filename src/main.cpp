#include<iostream>
#include<random>
#include<string>

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

	World world(50, 100);
	world.generate(userSeed);
	// Рисуем статическую карту в консоли
	world.drawMap();
	// Отображаем статические и динамические объекты
	world.render();

	return 0;
}