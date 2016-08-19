//
//  Game.cpp
//  Tetris_p3
//
//  Created by Buddha G on 8/4/14.
//  Copyright (c) 2014 Summer_2014_CS32. All rights reserved.
//

#include "Game.h"
#include "UserInterface.h"
#include <string>
#include <ctime>

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int TANK_X = 0;
const int TANK_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;






void Game::play()
{
    mTank->display(m_screen, TANK_X, TANK_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Imitris!");
    waitForEnter();  // [in UserInterface.h]
    
    for(;;)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_level++;
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{
    
}

bool Game::playOneLevel()
{
    return false;  // [Replace this with the code to play a level.]
}

int Game::GetRand (int pA, int pB)
{
    return rand () % (pB - pA + 1) + pA;
}

void Game::InitGame()
{
    // Init random numbers
    srand ((unsigned int) time(NULL));
    
    // First piece
    mPiece          = GetRand (0, 6);
    mRotation       = GetRand (0, 3);
    mPosX           = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
    mPosY           = mPieces->GetYInitialPosition (mPiece, mRotation);
    
    //  Next piece
    mNextPiece      = GetRand (0, 6);
    mNextRotation   = GetRand (0, 3);
    mNextPosX       = BOARD_WIDTH + 5;
    mNextPosY       = 5;
}
void Game::CreateNewPiece()
{
    // The new piece
    mPiece          = mNextPiece;
    mRotation       = mNextRotation;
    mPosX           = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
    mPosY           = mPieces->GetYInitialPosition (mPiece, mRotation);
    
    // Random next piece
    mNextPiece      = GetRand (0, 6);
    mNextRotation   = GetRand (0, 3);
}


void Game::DrawTank ()
{
    
    
}

