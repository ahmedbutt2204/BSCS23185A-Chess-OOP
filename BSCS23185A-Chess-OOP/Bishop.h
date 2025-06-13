#pragma once
#include"Piece.h"

class bishop : public Piece
{
public:
	char sym;
	bishop(int _r, int _c, board* _b, Color _C, char ch);
	virtual void drawpieces(int sr, int sc, int clr, int a);
	virtual bool islegalmove(int sr, int sc, int dr, int dc, int turn, board* b, player* pla, int psr, int psc, int pdr, int pdc);
	virtual char getpiecesymbol(int i, int j);
	virtual bool getcaslaval();
	virtual void setcaslaval(bool _set);


};

    