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



