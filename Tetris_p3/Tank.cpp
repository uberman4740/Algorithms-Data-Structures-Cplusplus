#include "Tank.h"
#include "UserInterface.h"
#include <vector>

void Tank::display(Screen& screen, int x, int y)
{
    std::vector<std::vector<char>> boundary(y+1, std::vector<char>(x+2,' '));
    for(int i= 0 ; i< y+1; i++)
    {
        boundary[i][0] = '@';
        boundary[i][x+1] = '@';
        
    }
    for(int j= 0 ; j< x+2; j++)
    {
        boundary[y][j]= '@';
    }
    for(int r= 0 ; r< y+1 ; r++)
    {
        for(int c= 0 ; c<x+2 ; c++)
        {
            screen.gotoXY(c, r);
            screen.printChar(boundary[r][c]);
        }
    }

}
Tank::Tank (Pieces *pPieces, int pScreenHeight)
 :mPieces(pPieces),mScreenHeight(pScreenHeight)
{
    InitBoard();
}
void Tank::InitBoard()
{
    for(int i = 0 ; i < BOARD_WIDTH ;i++)
        for(int j = 0; j < BOARD_HEIGHT;j++)
            mBoard[i][j] = POS_FREE ;
}

bool Tank::isGameover()
{
    for(int i = 0; i < BOARD_WIDTH;i++)
    {
        if(mBoard[i][0]==POS_FILLED)
            return true;
    }
    return false;
}

void Tank::DeleteLine (int pY)
{
    for(int j = pY; j > 0 ; j--)
        for (int i = 0; i< BOARD_WIDTH;i++)
            mBoard[i][j]= mBoard[i][j-1];
}

void Tank::DeletePossibleLines ()
{
	for (int j = 0; j < BOARD_HEIGHT; j++)
	{
		int i = 0;
		while (i < BOARD_WIDTH)
		{
			if (mBoard[i][j] != POS_FILLED) break;
			i++;
		}
        
		if (i == BOARD_WIDTH)
            DeleteLine (j);
	}
}

void Tank::StorePiece (int pX, int pY, int pPiece, int pRotation)
{
	// Store each block of the piece into the board
	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
		{
			// Store only the blocks of the piece that are not holes
			if (mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0)
				mBoard[i1][j1] = POS_FILLED;
		}
	}
}

bool Tank::IsPossibleMovement (int pX, int pY, int pPiece, int pRotation)
{
	// Checks collision with pieces already stored in the board or the board limits
	// This is just to check the 5x5 blocks of a piece with the appropiate area in the board
	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
		{
			// Check if the piece is outside the limits of the board
			if (i1 < 0 	||  i1 > BOARD_WIDTH  - 1	|| j1 > BOARD_HEIGHT - 1)
			{
				if (mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0)
					return 0;
			}
            
			// Check if the piece have collisioned with a block already stored in the map
			if (j1 >= 0)
			{
				if ((mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0) &&
					(!IsFreeBlock (i1, j1))	)
					return false;
			}
		}
	}
    
	// No collision
	return true;
}
/*
 ======================================
 Returns 1 (true) if the this block of the board is empty, 0 if it is filled
 
 Parameters:
 
 >> pX:		Horizontal position in blocks
 >> pY:		Vertical position in blocks
 ======================================
 */

bool Tank::IsFreeBlock (int pX, int pY)
{
	if (mBoard [pX][pY] == POS_FREE)
        return true;
    else
        return false;
}