#include "bishop.h"
#include <iostream>
#include"board.h"
using namespace std;
bishop::bishop(int _r, int _c, board* _b, Color _C, char ch)
    :Piece(_r, _c, _b, _C)
{
    this->sym = ch;
    this->casaval = false;
}

char bishop::getpiecesymbol(int i, int j)
{
    if (B->getpiece(i, j) == nullptr)
    {
        return '-';
    }
    return this->sym;
}

void bishop::drawpieces(int sr, int sc, int clr, int a)
{
    /*if (this->C == BLACK)
    {
        std::cout << "b";
    }

    if (this->C == WHITE)
    {
        std::cout << "B";
    }*/

    SetClr(clr);

    for (int i = 0; i < a - 2; i++)
    {
        for (int j = 0; j < a - 2; j++)
        {
            gotoRowCol(sr - 1 + i, sc - 1 + j);
            cout << char(-37);
        }
    }

    gotoRowCol(sr - 2, sc);
    cout << char(-37);

    gotoRowCol(sr + 2, sc);
    cout << char(-37);

    for (int i = 0; i < a; i++)
    {
        gotoRowCol(sr + 3, sc - 2 + i);
        cout << char(-37);
    }  

}
//pl
bool bishop::islegalmove(int sr, int sc, int dr, int dc, int turn, board* b, player* pla, int psr, int psc, int pdr, int pdc)
{
    return(isdiagonalmove(sr, sc, dr, dc) && (diagonalLTRpathclear(sr, sc, dr, dc, b) ||
        diagonalRTLpathclear(sr, sc, dr, dc, b)));

}

bool bishop::getcaslaval()
{
    return this->casaval;
}

void bishop::setcaslaval(bool _set)
{
    this->casaval = _set;
}