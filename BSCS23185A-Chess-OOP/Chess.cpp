#include "chess.h"
#include"Utility.h"
#include"rook.h"
#include"knight.h"
#include"bishop.h"
#include"queen.h"
#include<stack>
#include<chrono>
#include<iomanip>
#include<vector>


using namespace std::chrono_literals;
chess::chess(std::string p1, std::string p2, int ti)
{
	this->sr = 0;
	this->sc = 0;
	this->dr = 0;
	this->dc = 0;

	this->turn = WHITETURN;

	this->parray[0] = new player(p1, BLACK, ti);
	this->parray[1] = new player(p2, WHITE, ti);

	this->b = new board();
}

void chess::displayturnmsg(player* p)
{
	gotoRowCol(26, 75);
	std::cout << p->getpnamecolr() << " turns " << std::endl;
}

void emptybox(int Sr, int Sc, int height, int width, int clr)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((i == 0 || i == height - 1) && (j == 0 || j == 1 || j == 4 || j == 5))
			{
				gotoRowCol(i + Sr, j + Sc);
				SetClr(clr);
				std::cout << char(-37);
			}

			if ((i == 1 || i == 4 || i == 3) && (j == 0 || j == width - 1))
			{
				gotoRowCol(i + Sr, j + Sc);
				SetClr(clr);
				std::cout << char(-37);
			}

			// previous one :
			/*if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
			{

				gotoRowCol(i + Sr, j + Sc);
				SetClr(clr);
				std::cout << char(-37);
			}*/
		}
	}

	SetClr(WHITE);
}

void unemptybox(int Sr, int Sc, int height, int width, int clr)
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

void pawnemptybox(int Sr, int Sc, int height, int width, int clr)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
			{

				gotoRowCol(i + Sr, j + Sc);
				SetClr(clr);
				std::cout << char(-37);
			}
		}
	}
}




