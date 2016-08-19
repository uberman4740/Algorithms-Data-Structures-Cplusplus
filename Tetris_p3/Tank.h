#include "Pieces.h"
#ifndef TANK
#define TANK

class Screen;
#define BOARD_WIDTH 10  //Board width in block
#define BOARD_HEIGHT 20 //Board height in blocks
#define PIECE_BLOCKS 4


class Tank
{
public:
    Tank (Pieces* pPieces, int pScreenHeight);
    Tank (int x,int y)
    {
        x = BOARD_WIDTH;
        y = BOARD_HEIGHT;
    };
    void display(Screen& screen, int x, int y);
    bool isGameover();
    void DeletePossibleLines();
    bool IsPossibleMovement		(int pX, int pY, int pPiece, int pRotation);
    void StorePiece				(int pX, int pY, int pPiece, int pRotation);
    bool IsFreeBlock			(int pX, int pY);
  
    
private:
    void InitBoard();  // initialize the tank to POS_FREE
    Pieces* mPieces;
    int mScreenHeight;
    int mBoard[BOARD_WIDTH][BOARD_HEIGHT];
    enum {POS_FREE,POS_FILLED}; //
    void DeleteLine (int pY);
    
    
  
    
    
};

#endif // TANK_INCLUDED
