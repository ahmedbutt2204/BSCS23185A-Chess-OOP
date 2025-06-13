#pragma once
#include<Windows.h>
//chess board pieces colors
enum Color { BLACK = 0, WHITETURN = 1, WHITE = 15 };
//mouse functions and color function
void getRowColbyLeftClick(int& rpos, int& cpos);
void gotoRowCol(int rpos, int cpos);
void SetClr(int clr);




