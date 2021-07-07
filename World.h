#pragma once
#include<string>

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
	//void render();


private:
	/// <summary>
	/// ������ �������� ����
	/// </summary
	const unsigned int COLUMN_NUMBER;
	/// <summary>
	/// ������ �������� ����
	/// </summary>
	const unsigned int ROW_NUMBER;

	/// <summary>
	/// ������� �������� ��������� �������� ����
	/// </summary>
	char** currentFrameBuffer;

	/// <summary>
	/// ������� ���������� ��������� �������� ����
	/// </summary>
	char** nextFrameBuffer;
};

