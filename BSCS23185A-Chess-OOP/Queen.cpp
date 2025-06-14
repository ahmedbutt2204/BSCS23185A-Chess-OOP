#include "queen.h"
#include"board.h"
queen::queen(int _r, int _c, board* b, Color c, char ch)
    :Piece(_r, _c, b, c)
{
    this->sym = ch;
    this->casaval = false;
}