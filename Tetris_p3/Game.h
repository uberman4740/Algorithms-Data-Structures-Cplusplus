//
//  Game.h
//  Tetris_p3
//
//  Created by Buddha G on 8/4/14.
//  Copyright (c) 2014 Summer_2014_CS32. All rights reserved.
//

#ifndef __Tetris_p3__Game__
#define __Tetris_p3__Game__

#include <iostream>
#include "Tank.h"
#include "Pieces.h"
#include "Tank.h"
#include "UserInterface.h"
#include <string>
class Game
{
public:
    Game            (Tank *pTank, Pieces *pPieces, int pScreenHeight);
    
    void DrawScene ();
    void CreateNewPiece ();
    
    int mPosX, mPosY;               // Position of the piece that is falling down
    int mPiece, mRotation;          // Kind and rotation the piece that is falling down
    void play();
    
    //------
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
    // [Add other members as necessary.]
    
    
    
private:
    int mScreenHeight;              // Screen height in pixels
    int mNextPosX, mNextPosY;       // Position of the next piece
    int mNextPiece, mNextRotation;  // Kind and rotation of the next piece
    
    Tank *mTank;
    Pieces *mPieces;
   // IO *mIO;
    
    int GetRand (int pA, int pB);
    void InitGame();
    void DrawPiece (int pX, int pY, int pPiece, int pRotation);
    void DrawTank ();
    
    
    //----------
    Screen  m_screen;
    int     m_level;
};

#endif /* defined(__Tetris_p3__Game__) */
