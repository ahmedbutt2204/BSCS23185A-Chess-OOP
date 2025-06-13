#include "king.h"
#include"board.h"

king::king(int _r, int _c, board* b, Color c, char ch)
    :Piece(_r, _c, b, c)
{
    this->sym = ch;
    this->casaval = true;

}   


void king::drawpieces(int sr, int sc, int clr, int a)
{
    /*if (this->C == BLACK)
    {
        std::cout << "k";
    }

    if (this->C == WHITE)  
    {   
            std::cout << "K";
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

    for (int i = 0; i < a; i++)
    {
        gotoRowCol(sr - 2, sc - 2 + i);
        std::cout << char(-37);
    }


}

char king::getpiecesymbol(int i, int j)
{

    if (B->getpiece(i, j) == nullptr)
    {
        return '-';
    }
    return this->sym;
}

bool king::islegalmove(int sr, int sc, int dr, int dc, int turn, board* b, player* pla, int psr, int psc, int pdr, int pdc)
{
    Piece* pi = b->getpiece(sr, sc);
    Piece* pi1 = b->getpiece(dr, dc);

    if (pi != nullptr && pi->getcaslaval() == true && pi1 != nullptr &&
        pi1->getcaslaval() == true &&
        pi->ishorizonatalmove(sr, sc, dr, dc) &&
        pi->horizontalpathclear(sr, sc, dr, dc, b))
    {
        return true;
    }


    int rowchange = abs(sr - dr);
    int colschange = abs(sc - dc);

    return  (rowchange <= 1 && colschange <= 1) && ((ishorizonatalmove(sr, sc, dr, dc) && horizontalpathclear(sr, sc, dr, dc, b))
        || (isverticalmove(sr, sc, dr, dc) && verticalpathclear(sr, sc, dr, dc, b))
        || (isdiagonalmove(sr, sc, dr, dc) && (diagonalLTRpathclear(sr, sc, dr, dc, b) ||
            diagonalRTLpathclear(sr, sc, dr, dc, b))));

}

bool king::getcaslaval()
{
    return this->casaval;
}

void king::setcaslaval(bool _set)
{
    this->casaval = _set;
}