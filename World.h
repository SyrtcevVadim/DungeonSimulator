#pragma once
#include<string>

using std::string;

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
	//void render();


private:
	/// <summary>
	/// Ширина игрового поля
	/// </summary
	const unsigned int COLUMN_NUMBER;
	/// <summary>
	/// Высота игрового поля
	/// </summary>
	const unsigned int ROW_NUMBER;

	/// <summary>
	/// Матрица текущего состояния игрового поля
	/// </summary>
	char** currentFrameBuffer;

	/// <summary>
	/// Матрица следующего состояний игрового поля
	/// </summary>
	char** nextFrameBuffer;
};

