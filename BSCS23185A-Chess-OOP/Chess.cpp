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

void chess::findking(int& cr, int& cc)
{
	char ch = 0;
	if (this->turn == BLACK)
	{
		ch = 'k';
	}
	if (this->turn == WHITETURN)
	{
		ch = 'K';
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Piece* ptr = b->getpiece(i, j);

			if (ptr != nullptr && ptr->getpiecesymbol(i, j) == ch)
			{
				cr = i;
				cc = j;
				return;
			}
		}
	}

}


bool chess::check(int psr, int psc, int pdr, int pdc)
{
	turnchange();
	int cr = 0, cc = 0;
	findking(cr, cc);
	turnchange();

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (isvalidsource(i, j, this->parray[this->turn]) &&
				this->b->getpiece(i, j)->islegalmove(i, j, cr, cc, this->turn, this->b, this->parray[this->turn], psr, psc, pdr, pdc))
			{
				return true;
			}
		}
	}
	return false;

}

bool chess::selfcheck(int _sr, int _sc, int _dr, int _dc, int psr, int psc, int pdr, int pdc)
{
	int i = 0; int j = 0;
	Piece* ptr = b->getpiece(_dr, _dc);
	Piece* ptr1 = b->getpiece(_sr, _sc);
	Piece* ptr2 = nullptr;
	if (pdr != -1 && pdc != -1)
	{
		ptr2 = b->getpiece(pdr, pdc);
	}
	b->changeboard(_sr, _sc, _dr, _dc, this->b, this->turn, i, j, psr, psc, pdr, pdc);
	turnchange();
	bool ch = check(psr, psc, pdr, pdc);
	b->tempchangeboard(_sr, _sc, _dr, _dc, ptr, this->b, ptr1, i, j);
	if (pdr != -1 && pdc != -1)
	{
		b->getpieceem(pdr, pdc) = ptr2;
	}
	turnchange();
	return ch;
}

bool chess::checkmate(int psr, int psc, int pdr, int pdc)
{
	turnchange();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				for (int l = 0; l < 8; l++)
				{
					if (isvalidsource(i, j, this->parray[this->turn]) && isvaliddes(k, l, this->parray[this->turn]) &&
						b->getpiece(i, j) != nullptr && b->getpiece(i, j)->islegalmove(i, j, k, l, this->turn, this->b, this->parray[this->turn], psr, psc, pdr, pdc)
						&& selfcheck(i, j, k, l, psr, psc, pdr, pdc) == false)
					{
						turnchange();
						return false;
					}
				}
			}
		}
	}
	return true;
}

void chess::turnchange()
{
	this->turn = (this->turn + 1) % 2;
}


void drawundobutton()
{

	unemptybox(43, 72, 10, 10, BLUE);

	for (int i = 0; i < 6; i++)
	{
		gotoRowCol(48, 79 - i);
		std::cout << char(-37);
	}
	gotoRowCol(47, 75);
	std::cout << char(-37);

	gotoRowCol(46, 76);
	std::cout << char(-37);

	gotoRowCol(49, 75);
	std::cout << char(-37);

	gotoRowCol(50, 76);
	std::cout << char(-37);

	gotoRowCol(55, 75);
	std::cout << "Undo" << std::endl;
}

void drawredobutton()
{
	unemptybox(43, 90, 10, 10, BLUE);

	for (int i = 0; i < 6; i++)
	{
		gotoRowCol(48, 97 - i);
		std::cout << char(-37);
	}
	gotoRowCol(47, 96);
	std::cout << char(-37);

	gotoRowCol(46, 95);
	std::cout << char(-37);

	gotoRowCol(49, 96);
	std::cout << char(-37);

	gotoRowCol(50, 95);
	std::cout << char(-37);

	gotoRowCol(55, 93);
	std::cout << "Redo ";
}

bool undocheck(int f, int g)
{
	if ((f >= 42 && f <= 54) && (g >= 72 && g <= 82))
	{
		return true;
	}

	return false;
}

bool redocheck(int f, int g)
{
	if ((f >= 42 && f <= 54) && (g >= 89 && g <= 100))
	{
		return true;
	}

	return false;
}

void chess::castlecheck(board* ptr, int _sr, int _sc, int _t)
{
	if (ptr->getpiece(_sr, _sc) == nullptr)
	{
		return;
	}
	char ch = ptr->getpiece(_sr, _sc)->getpiecesymbol(_sr, _sc);

	if (_t == WHITETURN)
	{
		if (ch == 'K' || (ch == 'R' && _sr == 7 && _sc == 0) ||
			(ch == 'R' && _sr == 7 && _sc == 7))
		{
			ptr->getpiece(_sr, _sc)->setcaslaval(false);
		}
	}

	else if (_t == BLACK)
	{
		if (ch == 'k' || (ch == 'r' && _sr == 0 && _sc == 0) ||
			(ch == 'r' && _sr == 0 && _sc == 7))
		{
			ptr->getpiece(_sr, _sc)->setcaslaval(false);
		}
	}
}




































