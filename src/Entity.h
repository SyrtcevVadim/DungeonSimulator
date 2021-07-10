#pragma once
#include"Utilities.h"

class Entity
{
public:
	Entity(Position coordinate);
	/// <summary>
	/// Устанавливает координаты объекта
	/// </summary>
	void setPosition(Position coordinate);
	/// <summary>
	/// Возвращает координаты объетка
	/// </summary>
	Position getPosition();
	/// <summary>
	/// Возвращает цвет объекта
	/// </summary>
	Color getColor();
	/// <summary>
	/// Возвращает символ объекта
	/// </summary>
	char getSymbol();

	friend bool operator ==(const Entity& lVal, const Entity& rVal);
protected:
	/// <summary>
	/// Счётчик объектов
	/// </summary>
	static unsigned int counter;

	/// <summary>
	/// Хэш-число, позволяющее отличить один объект от другого
	/// </summary>
	unsigned int _hashValue;
	/// <summary>
	/// Координаты объетка на карте
	/// </summary>
	Position currentCoordinate;
	/// <summary>
	/// Цвет объекта
	/// </summary>
	Color color;
	/// <summary>
	/// Символ объекта
	/// </summary>
	char symbol;

	void setColor(Color color);
	void setSymbol(char symbol);
};

