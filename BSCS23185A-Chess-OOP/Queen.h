#pragma once
#include"Piece.h"
#include<iostream>

class queen :public Piece
{
public:
	char sym;
	queen(int _r, int _c, board* b, Color c, char ch);
	virtual void drawpieces(int sr, int sc, int clr, int a);
	virtual bool islegalmove(int sr, int sc, int dr, int dc, int turn, board* b, player* pla, int psr, int psc, int pdr, int pdc);
	virtual char getpiecesymbol(int i, int j);
	virtual bool getcaslaval();
	virtual void setcaslaval(bool _set);
};

