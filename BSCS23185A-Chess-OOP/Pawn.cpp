#include "pawn.h"
#include"king.h"
#include<iostream>
#include"chess.h"
#include"board.h"

pawn::pawn(int _r, int _c, board* b, Color c, char ch)
	:Piece(_r, _c, b, c)
{
	this->sym = ch;
	this->casaval = false;
}

void pawn::drawpieces(int sr, int sc, int clr, int a)
{
	/*if (this->C == BLACK)
	{
		std::cout << "p";
	}
	if (this->C == WHITE)
	{
		std::cout << "P";
	}*/

	SetClr(clr);

	for (int i = 0; i < a; i++)
	{
		gotoRowCol(sr, sc - 2 + i);
		std::cout << char(-37);
	}

	for (int j = 0; j < a; j++)
	{
		gotoRowCol(sr - 2 + j, sc);
		std::cout << char(-37);
	}


}

char pawn::getpiecesymbol(int i, int j)
{
	if (B->getpiece(i, j) == nullptr)
	{
		return '-';
	}

	return this->sym;
}

bool pawn::islegalmove(int sr, int sc, int dr, int dc, int turn, board* b, player* pla, int psr, int psc, int pdr, int pdc)
{
	// em-passant move of the pawn: 


	int rowchange = sr - dr;
	int colschange = sc - dc;
	int capcheck = rowchange - colschange;


	if (turn == WHITETURN && pdr != -1 && pdc != -1 && b->getpiece(pdr, pdc) != nullptr && b->getpiece(pdr, pdc)->getpiecesymbol(pdr, pdc) == 'p'
		&& psr == 1 && pdr == 3 && sr == pdr && abs(pdc - sc) == 1)
	{
		if (rowchange == 1 && pdc == dc && b->getpiece(dr, dc) == nullptr)
		{
			return true;
		}
	}

	if (turn == BLACK && pdr != -1 && pdc != -1 && b->getpiece(pdr, pdc) != nullptr && b->getpiece(pdr, pdc)->getpiecesymbol(pdr, pdc) == 'P'
		&& psr == 6 && pdr == 4 && sr == pdr && abs(pdc - sc) == 1)
	{
		if (rowchange == -1 && pdc == dc && b->getpiece(dr, dc) == nullptr)
		{
			return true;
		}
	}


	// initial pawn movement :
	//b->getpieceem(sr, sc) = new king(sr,sc,b,WHITE);


	// diagonal capture movement of pawn :

	if (turn == WHITETURN && rowchange == 1 && abs(colschange) == 1 && b->getpiece(dr, dc) != nullptr && !ismypiece(dr, dc, pla))
	{
		return true;
	}

	if (turn == BLACK && rowchange == -1 && abs(colschange) == 1 && b->getpiece(dr, dc) != nullptr && !ismypiece(dr, dc, pla))
	{
		return true;
	}



	if (sr == 1 || sr == 6)
	{
		if (turn == WHITETURN)
		{
			return ((rowchange == 1 || rowchange == 2) && (isverticalmove(sr, sc, dr, sc) && verticalpathclear(sr, sc, dr, dc, b)) && colschange == 0 && b->getpiece(dr, dc) == nullptr);
		}

		if (turn == BLACK)
		{
			return ((rowchange == -1 || rowchange == -2) && (isverticalmove(sr, sc, dr, sc) && verticalpathclear(sr, sc, dr, dc, b)) && colschange == 0 && b->getpiece(dr, dc) == nullptr);
		}
	}



	// normal vertical movement of pawm :


	if (sr > 1 && sr < 6)
	{
		if (turn == WHITETURN)
		{
			return (rowchange == 1 && isverticalmove(sr, sc, dr, sc) && verticalpathclear(sr, sc, dr, dc, b) && colschange == 0 && b->getpiece(dr, dc) == nullptr);
		}

		if (turn == BLACK)
		{
			return (rowchange == -1 && isverticalmove(sr, sc, dr, sc) && verticalpathclear(sr, sc, dr, dc, b) && colschange == 0 && b->getpiece(dr, dc) == nullptr);
		}
	}

	 
	return false;
}
 
bool pawn::getcaslaval()
{
	return this->casaval;
}
//setted
void pawn::setcaslaval(bool _set)
{
	this->casaval = _set;
}

