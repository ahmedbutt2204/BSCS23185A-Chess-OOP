#include "queen.h"
#include"board.h"
queen::queen(int _r, int _c, board* b, Color c, char ch)
    :Piece(_r, _c, b, c)
{
    this->sym = ch;
    this->casaval = false;
}

void queen::drawpieces(int sr, int sc, int clr, int a)
{
    /*if (this->C == BLACK)
    {
        std::cout << "q";
    }

    if (this->C == WHITE)
    {
    std:: cout << "Q";
    }*/
    SetClr(clr);
    for (int i = 0; i < a - 2; i++)
    {
        gotoRowCol(sr, sc - 1 + i);
        std::cout << char(-37);
    }

    for (int j = 0; j < a - 2; j++)
    {
        gotoRowCol(sr - 2 + j, sc);
        std::cout << char(-37);
    }
    for (int i = 0; i < a; i++)
    {
        gotoRowCol(sr + 1, sc - 2 + i);
        std::cout << char(-37);
    }

}

char queen::getpiecesymbol(int i, int j)
{
    if (B->getpiece(i, j) == nullptr)
    {
        return '-';
    }
    return this->sym;
}


bool queen::islegalmove(int sr, int sc, int dr, int dc, int turn, board* b, player* pla, int psr, int psc, int pdr, int pdc)
{
    return (ishorizonatalmove(sr, sc, dr, dc) && horizontalpathclear(sr, sc, dr, dc, b))
        || (isverticalmove(sr, sc, dr, dc) && verticalpathclear(sr, sc, dr, dc, b))
        || (isdiagonalmove(sr, sc, dr, dc) && (diagonalLTRpathclear(sr, sc, dr, dc, b) ||
            diagonalRTLpathclear(sr, sc, dr, dc, b)));

}

bool queen::getcaslaval()
{
    return this->casaval;
} 

void queen::setcaslaval(bool _set)
{
    this->casaval = _set;
}
//getter for queen 