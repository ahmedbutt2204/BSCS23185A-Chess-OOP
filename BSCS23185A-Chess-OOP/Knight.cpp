#include "knight.h"
#include<iostream>
#include"board.h"
knight::knight(int _r, int _c, board* b, Color c, char ch)
    :Piece(_r, _c, b, c)
{
    this->sym = ch;
    this->casaval = false;
}

void knight::drawpieces(int sr, int sc, int clr, int a)
{
    /*if (this->C == BLACK)
    {
        std::cout << "l";
    }

    if (this->C==WHITE)
    {
        std::cout << "L";
    }*/

    SetClr(clr);
    for (int i = 0; i < a - 2; i++)
    {
        gotoRowCol(sr + 2, sc - 1 + i);
        std::cout << char(-37);
    }


    for (int i = 0; i < a - 2; i++)
    {
        gotoRowCol(sr - i + 1, sc);
        std::cout << char(-37);
    }


    for (int i = 0; i < a - 2; i++)
    {
        gotoRowCol(sr - 2, sc - 1 + i);
        std::cout << char(-37);
    }
}

char knight::getpiecesymbol(int i, int j)
{
    if (B->getpiece(i, j) == nullptr)
    {
        return '-';
    }
    return this->sym;
}

bool knight::islegalmove(int sr, int sc, int dr, int dc, int turn, board* b, player* pla, int psr, int psc, int pdr, int pdc)
{
    int rowchange = abs(sr - dr);
    int colschange = abs(sc - dc);

    return (rowchange == 2 && colschange == 1 && !ismypiece(dr, dc, pla))
        || (rowchange == 1 && colschange == 2 && !ismypiece(dr, dc, pla));

}

bool knight::getcaslaval()
{
    return this->casaval; 
}

void knight::setcaslaval(bool _set)
{
    this->casaval = _set;
}