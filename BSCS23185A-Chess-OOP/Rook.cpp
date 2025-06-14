#include "rook.h"
#include<iostream>
#include"board.h"

rook::rook(int _r, int _c, board* b, Color c, char ch)
    :Piece(_r, _c, b, c)
{
    this->sym = ch;
    this->casaval = true;
}

void rook::drawpieces(int sr, int sc, int clr, int a)
{
    /*if (this->C == BLACK)
    {
        std::cout << "r";
    }

    if (this->C == WHITE)
    {
        std::cout << "R";
    }*/
    SetClr(clr);
    for (int i = 0; i < a - 2; i++)
    {
        for (int j = 0; j < a - 2; j++)
        {
            gotoRowCol(sr - 1 + i, sc - 1 + j);
            std::cout << char(-37);
        }
    }


    for (int i = 0; i < a; i++)
    {
        gotoRowCol(sr + 2, sc - 2 + i);
        std::cout << char(-37);
    }

    gotoRowCol(sr - 2, sc);
    std::cout << char(-37);
}

char rook::getpiecesymbol(int i, int j)
{
    if (B->getpiece(i, j) == nullptr)
    {
        return '-';
    }
    return this->sym;
}

bool rook::islegalmove(int sr, int sc, int dr, int dc, int turn, board* b, player* pla, int psr, int psc, int pdr, int pdc)
{
    //Fix incorrect parameter in horizontal move check logic
    return (ishorizonatalmove(sr, sc, dr, sc) && horizontalpathclear(sr, sc, dr, dc, b))
        || (isverticalmove(sr, sc, dr, dc) && verticalpathclear(sr, sc, dr, dc, b));
}

bool rook::getcaslaval()
{
    return this->casaval;
}

void rook::setcaslaval(bool _set)
{
    this->casaval = _set;
}



