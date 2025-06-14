#include "board.h"
#include"bishop.h"
#include"pawn.h"
#include"king.h"
#include"knight.h"
#include"queen.h"
#include"rook.h"
#include "chess.h"
#include"Piece.h"

board::board()
{
	this->ps = new Piece * *[8];

	for (int r = 0; r < 8; r++)
	{
		ps[r] = new Piece * [8];

		for (int c = 0; c < 8; c++)
		{
			if (r == 1)
			{
				ps[r][c] = new pawn(r, c, this, BLACK, 'p');
			}

			else if (r == 6)
			{
				ps[r][c] = new pawn(r, c, this, WHITE, 'P');
			}

			else if ((r == 0 && c == 0) || (r == 0 && c == 7))
			{
				ps[r][c] = new rook(r, c, this, BLACK, 'r');
			}

			else if ((r == 0 && c == 1) || (r == 0 && c == 6))
			{
				ps[r][c] = new knight(r, c, this, BLACK, 'l');
			}

			else if ((r == 0 && c == 2) || (r == 0 && c == 5))
			{
				ps[r][c] = new bishop(r, c, this, BLACK, 'b');
			}

			else if ((r == 0 && c == 3))
			{
				ps[r][c] = new queen(r, c, this, BLACK, 'q');
			}

			else if ((r == 0 && c == 4))
			{
				ps[r][c] = new king(r, c, this, BLACK, 'k');
			}

			else if ((r == 7 && c == 0) || (r == 7 && c == 7))
			{
				ps[r][c] = new rook(r, c, this, WHITE, 'R');
			}

			else if ((r == 7 && c == 1) || (r == 7 && c == 6))
			{
				ps[r][c] = new knight(r, c, this, WHITE, 'L');
			}

			else if ((r == 7 && c == 2) || (r == 7 && c == 5))
			{
				ps[r][c] = new bishop(r, c, this, WHITE, 'B');
			}

			else if ((r == 7 && c == 3))
			{
				ps[r][c] = new queen(r, c, this, WHITE, 'Q');
			}

			else if ((r == 7 && c == 4))
			{
				ps[r][c] = new king(r, c, this, WHITE, 'K');
			}

			else
			{
				ps[r][c] = nullptr;
			}

		}

	}


}


void board::drawbox(int sr, int sc, int height, int width, int clr, int p1, int p2)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			gotoRowCol(i + sr, j + sc);
			SetClr(clr);
			std::cout << char(-37);
		}
	}

	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			if (r == height / 2 && c == width / 2 && ps[p1][p2] != nullptr)
			{
				int color = ps[p1][p2]->getpiececolor();
				ps[p1][p2]->drawpieces(r + sr, c + sc, color, 5);
				SetClr(clr);
			}

		}
	}

}


void board::displayboard(int height, int width)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((i + j) % 2 == 0)
			{
				drawbox(rows / 7 + i * height, 2 + j * width, height, width, YELLOW, i, j);
			}
			else
			{
				drawbox(rows / 7 + i * height, 2 + j * width, height, width, GREEN, i, j);
			}
		}
	}

}


Piece* board::getpiece(int i, int j)
{
	return this->ps[i][j];

}

Piece*& board::getpieceem(int i, int j)
{
	return this->ps[i][j];

}


void board::changeboard(int sr, int sc, int dr, int dc, board* _b, int turn, int& i, int& j, int psr, int psc, int pdr, int pdc)
{
	Piece* ptr = _b->getpiece(sr, sc);
	Piece* ptr1 = _b->getpiece(dr, dc);

	/*char ch = ->getpiecesymbol(sr,sc);
	char ch1 = _b->getpiece(dr, dc)->getpiecesymbol(dr,dc);

	ch == 'K' && ch1 == 'R'*/
	if (ptr != nullptr && ptr1 != nullptr && (ptr->getpiecesymbol(sr, sc) == 'k' || ptr->getpiecesymbol(sr, sc) == 'K')
		&& (ptr1->getpiecesymbol(dr, dc) == 'R' || ptr1->getpiecesymbol(dr, dc) == 'r'))
	{
		if ((sr == 7 && sc == 4 && dr == 7 && dc == 7) || (sr == 0 && sc == 4 && dr == 0 && dc == 7))
		{
			this->ps[sr][sc + 2] = this->ps[sr][sc];
			this->ps[sr][sc] = nullptr;
			this->ps[dr][dc - 2] = this->ps[dr][dc];
			this->ps[dr][dc] = nullptr;
			i = sc + 2;
			j = dc - 2;
		}

		if ((sr == 7 && sc == 4 && dr == 7 && dc == 0) || (sr == 0 && sc == 4 && dr == 0 && dc == 0))
		{
			this->ps[sr][sc - 2] = this->ps[sr][sc];
			this->ps[sr][sc] = nullptr;
			this->ps[dr][dc + 3] = this->ps[dr][dc];
			this->ps[dr][dc] = nullptr;
			i = sc - 2;
			j = dc + 3;
		}
	}
	else
	{


		if (turn == WHITETURN && _b->getpiece(sr, sc)->getpiecesymbol(sr, sc) == 'P'
			&& ((sc - dc == -1 && _b->getpiece(dr, dc) == nullptr)
				|| (sc - dc == 1 && _b->getpiece(dr, dc) == nullptr)))
		{
			this->ps[dr][dc] = this->ps[sr][sc];
			this->ps[sr][sc] = nullptr;
			this->ps[sr][dc] = nullptr;
		}

		else if (turn == BLACK && _b->getpiece(sr, sc)->getpiecesymbol(sr, sc) == 'p'
			&& ((sc - dc == -1 && _b->getpiece(dr, dc) == nullptr)
				|| (sc - dc == 1 && _b->getpiece(dr, dc) == nullptr)))
		{
			this->ps[dr][dc] = this->ps[sr][sc];
			this->ps[sr][sc] = nullptr;
			this->ps[sr][dc] = nullptr;
		}

		else
		{
			this->ps[dr][dc] = this->ps[sr][sc];
			this->ps[sr][sc] = nullptr;
		}


	}


}
