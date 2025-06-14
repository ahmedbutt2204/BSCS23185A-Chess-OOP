#include "rook.h"
#include<iostream>
#include"board.h"

rook::rook(int _r, int _c, board* b, Color c, char ch)
    :Piece(_r, _c, b, c)
{
    this->sym = ch;
    this->casaval = true;
}
