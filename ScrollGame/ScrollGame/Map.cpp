#include "Map.h"
#include "Log.h"
#include <iostream>
Map::Map()
{
	Log::Complete("[ Allocated Map ]");
}

Map::~Map()
{
	Log::Complete("[ Deallocated Map ]");
}

void Map::Update()
{
}

void Map::Render()
{
	//int consoleWidth = 800; // CMD 창의 너비 (픽셀 단위)
	//int fontWidth = 8;      // 폰트의 폭 (픽셀 단위)

	//int charsPerLine = consoleWidth / fontWidth; // 한 줄에 들어갈 문자 수
	////std::cout << "Number of 2-byte chars per line: " << charsPerLine << std::endl;

	//std::string line(charsPerLine, '□');
	//std::cout << line << std::endl;
	//90
	
	int val = 61;
	for (int y = 0; y < val; y++)
	{

		for (int x = 0; x < val; x++)
		{
			//Log::Cout("□");
			if (x == 0 && y == 0)
			{
				std::cout << "■";
				continue;
			}
			if (x == 0 && y == val - 1)
			{
				std::cout << "■";
				continue;
			}
			if (x == val - 1 && y == 0)
			{
				std::cout << "■"<<std::endl;
				continue;
			}
			if (x == val - 1 && y == val - 1)
			{
				std::cout << "■"<<std::endl;
				continue;
			}

			if (x == val/2 && y == val / 2)
			{
				std::cout << "■";
				continue;
			}

			if (x == val-1)
			{
				Log::Cout("□");
				continue;
			}

			std::cout << "□";
		}
	}
	//COORD cur;
	//cur.X = 0;
	//cur.Y = 0;
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
	//std::cout << "■";
	//cur.X = 1;
	//cur.Y = 0;
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
	//std::cout << "■";
	//cur.X = 0;
	//cur.Y = 60;
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
	//std::cout << "■";
	//cur.X = 1;
	//cur.Y = 60;
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
	//std::cout << "■";

	//cur.X = 2;
	//cur.Y = 0;
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
	//std::cout << "■";

	//cur.X = 2;
	//cur.Y = 60;
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
	//std::cout << "■";
	//Log::Cout(line);
}

void Map::GenerateMap()
{
}
