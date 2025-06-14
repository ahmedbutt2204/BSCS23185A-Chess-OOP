#pragma once
#include "board.h";
#include "Piece.h";
#include "player.h"
#include "Utility.h"
#include <iostream>


#define rows 81
#define columns 118
#define colorBlack   0
#define BLUE         1
#define GREEN        2
#define CYAN         3
#define RED          4
#define MAGENTA      5
#define BROWN        6
#define LIGHTGRAY    7
#define DARKGRAY     8
#define LIGHTBLUE    9
#define LIGHTGREEN   10
#define LIGHTCYAN    11
#define LIGHTRED     12
#define LIGHTMAGENTA 13
#define YELLOW       14
#define colorWhite   15



class chess
{
private:
	int sr; int sc;
	int dr; int dc;
	int turn;
	player* parray[2];
	board* b;
public:

	chess(std::string p1, std::string p2, int ti);
	void displayturnmsg(player* a);
	int getturn();
	//bool ismypiece(int i, int j, player* p);
	void sourceposition(int& _f, int& _g);
	bool isvalidsource(int i, int j, player* p);
	void desposition();
	bool isvaliddes(int i, int j, player* p);
	void turnchange();
	void computehiglight(bool**& bmap, int psr, int psc, int pdr, int pdc);
	void higlighting(bool**& bmap, int height, int width);
	void unhiglighting(bool**& bmap, int height, int width);
	bool checkpawnpromote(char ch);
	void pawnpromotiongraphics(int height, int width, int clr, board* b, int _dr, int _dc);








