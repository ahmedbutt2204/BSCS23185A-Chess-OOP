#include <iostream>
#include<conio.h>
#include"chess.h";


void mainbox(int Sr, int Sc, int height, int width, int clr)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			/*if ((i == 0 || i == height - 1) && (j == 0 || j == 1 || j == 4 || j == 5))
			{
				if ((i + j % 2) == 0)
				{
					SetClr(YELLOW);
				}
				gotoRowCol(i + Sr, j + Sc);

				std::cout << char(-37);
			}

			if ((i == 1 || i == 4 || i == 3) && (j == 0 || j == width - 1))
			{
				gotoRowCol(i + Sr, j + Sc);

				if ((i + j % 2) == 1)
				{
					SetClr(GREEN);
				}
				std::cout << char(-37);
			}*/

			// previous one :
			if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
			{

				gotoRowCol(i + Sr, j + Sc);
				SetClr(clr);
				std::cout << char(-37);
			}
		}
	}

	SetClr(WHITE);
}


void line(std::string& p1, std::string& p2, int& ti)
{
	SetClr(BLUE);
	for (int i = 0; i < 53; i++)
	{
		gotoRowCol(30, 31 + i);
		std::cout << char(-37);
	}
	SetClr(WHITE);
	gotoRowCol(27, 48);
	std::cout << "PLAYER's NAME :  ";
	gotoRowCol(40, 34);
	std::cout << "PLAYER 1 NAME (BLACK) :  ";
	std::cin >> p1;
	gotoRowCol(50, 34);
	std::cout << "PLAYER 2 NAME (WHITE) :  ";
	std::cin >> p2;
	gotoRowCol(58, 34);
	std::cout << "TIME LIMIT :  ";
	std::cin >> ti;
}

int main()
{
	mainbox(22, 30, 45, 55, BLUE);
	std::string p1;
	std::string p2;
	int ti = 0;
	line(p1, p2, ti);

	chess C(p1, p2, ti);
	Sleep(10);
	system("cls");
	C.chessplay();

	_getch();  // Wait for key before exiting
	return 0;
}


