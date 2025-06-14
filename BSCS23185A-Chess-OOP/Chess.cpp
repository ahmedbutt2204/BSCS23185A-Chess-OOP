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

int chess::getturn()
{
	return this->turn;
}

void chess::sourceposition(int& _f, int& _g)
{
	getRowColbyLeftClick(this->sr, this->sc);
	_f = this->sr;
	_g = this->sc;
	this->sr = this->sr - 2;
	this->sr = this->sr / 8 - 1;

	this->sc = this->sc / 8;
}

void chess::desposition()
{
	getRowColbyLeftClick(this->dr, this->dc);
	this->dr = this->dr - 2;
	this->dr = this->dr / 8 - 1;

	this->dc = this->dc / 8;

}


bool chess::isvaliddes(int i, int j, player* pla)
{
	if (this->sr < 0 || this->sc < 0 || this->sr >= 8 || this->sc >= 8)
	{
		return false;
	}
	Piece* ptr = b->getpiece(i, j);
	if (ptr == nullptr)
	{
		return true;
	}

	Piece* ptr1 = b->getpiece(this->sr, this->sc);
	if (ptr1 == nullptr)
	{
		return false;
	}

	char ch = ptr1->getpiecesymbol(this->sr, this->sc);
	char ch1 = ptr->getpiecesymbol(i, j);
	if ((ch == 'K' || ch == 'k') && (ch1 == 'R' || ch1 == 'r')
		&& this->b->getpiece(i, j)->horizontalpathclear(this->sr, this->sc, i, j, this->b))
	{
		return true;
	}

	return !(ptr->ismypiece(i, j, pla));
}


bool chess::isvalidsource(int i, int j, player* p)
{
	if (this->sr < 0 || this->sc < 0 || this->sr >= 8 || this->sc >= 8)
	{
		return false;
	}

	Piece* ptr = b->getpiece(i, j);
	if (ptr == nullptr)
	{
		return false;
	}
	return ptr->ismypiece(i, j, p);

}

void chess::computehiglight(bool**& bmap, int psr, int psc, int pdr, int pdc)
{
	bmap = new bool* [8];
	for (int i = 0; i < 8; i++)
	{
		bmap[i] = new bool[8] {};
	}

	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			if (isvaliddes(r, c, this->parray[this->turn]) &&
				this->b->getpiece(this->sr, this->sc)->islegalmove(sr, sc, r, c, turn, b, parray[this->turn], psr, psc, pdr, pdc)
				&& selfcheck(this->sr, this->sc, r, c, psr, psc, pdr, pdc) == false)
			{
				bmap[r][c] = true;
			}
		}
	}

}

void chess::higlighting(bool**& bmap, int height, int width)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (bmap[i][j] == true)
			{
				emptybox(rows / 7 + height * i + 1, 3 + j * width, height - 2, width - 2, BLUE);
			}
		}
	}
}

void chess::unhiglighting(bool**& bmap, int height, int width)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (bmap[i][j] == true)
			{
				if ((i + j) % 2 == 0)
				{
					unemptybox(rows / 7 + height * i + 1, 3 + j * width, height - 2, width - 2, YELLOW);
				}
				else
				{
					unemptybox(rows / 7 + height * i + 1, 3 + j * width, height - 2, width - 2, GREEN);
				}

			}
		}
	}
}
bool chess::checkpawnpromote(char ch)
{
	if (ch != 'P' && ch != 'p')
	{
		return false;
	}

	if (turn == WHITETURN && this->dr == 0)
	{
		return true;
	}

	if (turn == BLACK && this->dr == 7)
	{
		return true;
	}

	return false;

}


void chess::pawnpromotiongraphics(int height, int width, int clr, board* b, int _dr, int _dc)
{
	system("cls");
	gotoRowCol(20, 22);
	std::cout << "Choose your pawn promotion piece : " << std::endl;
	for (int c = 0; c < 4; c++)
	{
		//pawnemptybox(rows / 7 + height * 1 + 1, 3 + c * width, height * 2, width * 2, BLUE);
		pawnemptybox(23, c * width + 22, height, width, clr);
	}

	// rook shape :

	gotoRowCol(25, 28);
	std::cout << char(-37);

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			gotoRowCol(26 + i, j + 26);
			std::cout << char(-37);
			if (i == 5)
			{
				gotoRowCol(26 + i, j + 26 - 1);
				std::cout << char(-37);

				if (j == 4)
				{
					gotoRowCol(26 + i, j + 26 + 1);
					std::cout << char(-37);
				}
			}
		}
	}

	gotoRowCol(38, 26);
	std::cout << " ROOK  " << std::endl;

	// knight shape :

	for (int i = 0; i < 5; i++)
	{
		gotoRowCol(25, 39 + i);
		std::cout << char(-37);
	}

	for (int i = 0; i < 6; i++)
	{
		gotoRowCol(26 + i, 41);
		std::cout << char(-37);
	}

	for (int i = 0; i < 5; i++)
	{
		gotoRowCol(32, 39 + i);
		std::cout << char(-37);
	}

	gotoRowCol(38, 38);
	std::cout << " KNIGHT  " << std::endl;


	// Bishop :

	gotoRowCol(25, 54);
	std::cout << char(-37);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			gotoRowCol(26 + i, j + 52);
			std::cout << char(-37);
		}
	}

	gotoRowCol(32, 54);
	std::cout << char(-37);

	for (int i = 0; i < 7; i++)
	{
		gotoRowCol(33, i + 51);
		std::cout << char(-37);
	}

	gotoRowCol(38, 51);
	std::cout << " BISHOP  " << std::endl;

	// queen :

	gotoRowCol(27, 67);
	std::cout << char(-37);

	for (int i = 1; i <= 5; i++)
	{
		for (int j = 5; j > i; j--)
		{
			gotoRowCol(28 + i - 1, 67 - j);
			std::cout << " ";
		}

		for (int c = 0; c < 2 * i - 1; c++)
		{
			gotoRowCol(28 + i - 1, 68 - i + c);
			std::cout << char(-37);
		}

	}

	gotoRowCol(38, 65);
	std::cout << "QUEEN ";

	// mouse input :
	int r, c;
	getRowColbyLeftClick(r, c);

	if (r >= 22 && r <= 36)
	{
		if (c >= 22 && c <= 35)
		{

			b->getpieceem(this->dr, this->dc) = new rook(this->dr, this->dc, b, b->getpiece(dr, dc)->getpiececolor(), this->turn);
		}

		else if (c >= 36 && c <= 49)
		{
			b->getpieceem(this->dr, this->dc) = new knight(this->dr, this->dc, b, b->getpiece(dr, dc)->getpiececolor(), this->turn);
		}

		else if (c >= 50 && c <= 63)
		{
			b->getpieceem(this->dr, this->dc) = new bishop(this->dr, this->dc, b, b->getpiece(dr, dc)->getpiececolor(), this->turn);
		}
		//Display pawn promotion UI and handle piece selection
		else if (c >= 64 && c <= 77)
		{
			b->getpieceem(this->dr, this->dc) = new queen(this->dr, this->dc, b, b->getpiece(dr, dc)->getpiececolor(), this->turn);
		}
	}


}

























