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
	//Declare methods to draw board cells and display full board
	void changeboard(int sr, int sc, int dr, int dc, board* _b, int turn, int& i, int& j, int psr, int psc, int pdr, int pdc);
	void tempchangeboard(int sr, int sc, int dr, int dc, Piece* p, board* b, Piece* p1, int i, int j);

};