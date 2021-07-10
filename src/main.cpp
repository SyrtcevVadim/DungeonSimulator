#include<iostream>
#include<random>
#include<string>

#include"../lib/rlutil/rlutil.h"
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
	World world(50, 100);
	world.generate();
	// Рисуем первый кадр в консоли
	world.drawMap();

	// Цикл рендеринга
	while (1)
	{	
		rlutil::msleep(300);
		world.render();
	}

	return 0;
}