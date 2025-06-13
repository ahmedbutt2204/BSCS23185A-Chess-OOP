#include "Piece.h"
#include<iostream>
#include"chess.h"


Piece::Piece(int _r, int _c, board* b, Color c)
{
	this->rpos = _r;
	this->cpos = _c;
	this->C = c;
	this->B = b;

}

void Piece::move(int _r, int _c)
{
	this->rpos = _r;
	this->cpos = _c;
}

Color Piece::getpiececolor()
{
	return this->C;
}

bool Piece::ismypiece(int i, int j, player* pla)
{
	Piece* p = B->getpiece(i, j);
	if (p == nullptr)
	{
		return false;
	}

	return (p != nullptr && pla->getcolor() == p->getpiececolor());
}

bool Piece::ishorizonatalmove(int _sr, int _sc, int _dr, int _dc)
{
	return (_sr == _dr);

}

bool Piece::isverticalmove(int _sr, int _sc, int _dr, int _dc)
{
	return (_sc == _dc);

}

bool Piece::isdiagonalmove(int _sr, int _sc, int _dr, int _dc)
{
	return abs(_sr - _dr) == abs(_sc - _dc);

}

bool Piece::horizontalpathclear(int _sr, int _sc, int _dr, int _dc, board* _b)
{
	int el = abs(_sc - _dc) - 1;
	int colschange = 0;
	if (_sc < _dc)
	{
		colschange = _sc;
	}

	if (_sc > _dc)
	{
		colschange = _dc;
	}

	for (int i = 1; i <= el; i++)
	{
		if (_b->getpiece(_sr, colschange + i) != nullptr)
		{
			return false;
		}
	}

	return true;
}

bool Piece::verticalpathclear(int _sr, int _sc, int _dr, int _dc, board* _b)
{
	int el = abs(_sr - _dr) - 1;
	int rowchange = 0;
	if (_sr < _dr)
	{
		rowchange = _sr;
	}

	if (_sr > _dr)
	{
		rowchange = _dr;
	}

	for (int i = 1; i <= el; i++)
	{
		if (_b->getpiece(rowchange + i, _sc) != nullptr)
		{
			return false;
		}
	}

	return true;
}

bool Piece::diagonalLTRpathclear(int _sr, int _sc, int _dr, int _dc, board* _b)
{
	int ri = 0; int ci = 0;
	int el = 0;
	if (_sr < _dr && _sc < _dc)
	{
		ri = _sr;
		ci = _sc;
	}

	else if (_sr > _dr && _sc > _dc)
	{
		ri = _dr;
		ci = _dc;
	}
	else
	{
		return false;
	}

	el = abs(_sr - _dr) - 1;

	for (int i = 1; i <= el; i++)
	{
		if (_b->getpiece(ri + i, ci + i) != nullptr)
		{
			return false;
		}
	}

	return true;
}

bool Piece::diagonalRTLpathclear(int _sr, int _sc, int _dr, int _dc, board* _b)
{
	int ri = 0; int ci = 0;
	int el = 0;

	if (_sr > _dr && _sc < _dc)
	{
		ri = _dr;
		ci = _dc;
	}

	else if (_sr < _dr && _sc > _dc)
	{
		ri = _sr;
		ci = _sc;
	}
	else
	{
		return false;
	} 
	//r
	el = abs(_sr - _dr) - 1;

	for (int i = 1; i <= el; i++)
	{
		if (_b->getpiece(i + ri, ci - i) != nullptr)
		{
			return false;
		}
	}

	return true;
}