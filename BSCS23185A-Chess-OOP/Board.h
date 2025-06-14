#pragma once

class Piece;

class board
{
private:
	Piece*** ps;

public:
	board();
	board(const board& h1);
	const board* operator=(const board* h1);
	void drawbox(int sr, int sc, int height, int width, int clr, int p1, int p2);
	void displayboard(int height, int width);
	Piece* getpiece(int i, int j);
	Piece*& getpieceem(int i, int j);
