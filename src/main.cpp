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
	world.drawMap();

	return 0;
}