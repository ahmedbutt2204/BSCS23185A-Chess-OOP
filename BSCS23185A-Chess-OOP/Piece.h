#pragma once
#include"Utility.h"
#include"player.h"
// forward declaration :
class board;

class Piece
{
protected:
	int rpos;
	int cpos;
	board* B;
	Color C;
	bool casaval;

public:
	Piece(int _r, int _c, board* b, Color c);
	virtual void drawpieces(int sr, int sc, int clr, int a) = 0;
	  //int sr, int sc, int height, int width, Color c(draw arguments with graphics)
	void move(int _r, int _c);
	bool ismypiece(int i, int j, player* p);
	bool ishorizonatalmove(int _sr, int _sc, int _dr, int _dc);
	bool isverticalmove(int _sr, int _sc, int _dr, int _dc);
	bool isdiagonalmove(int _sr, int _sc, int _dr, int _dc);
	bool horizontalpathclear(int _sr, int _sc, int _dr, int _dc, board* _b);
	bool verticalpathclear(int _sr, int _sc, int _dr, int _dc, board* _b);
	bool diagonalLTRpathclear(int _sr, int _sc, int _dr, int _dc, board* _b);
	bool diagonalRTLpathclear(int _sr, int _sc, int _dr, int _dc, board* _b);
	virtual bool islegalmove(int sr, int sc, int dr, int dc, int turn, board* b, player* pla, int psr, int psc, int pdr, int pdc) = 0;
	virtual char getpiecesymbol(int i, int j) = 0;
	virtual bool getcaslaval() = 0;
	virtual void setcaslaval(bool _set) = 0;
	Color getpiececolor();



};

