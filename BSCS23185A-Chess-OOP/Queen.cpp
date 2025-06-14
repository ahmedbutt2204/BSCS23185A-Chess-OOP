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
