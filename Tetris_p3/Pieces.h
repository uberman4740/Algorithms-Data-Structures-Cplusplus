//
//  Pieces.h
//  Tetris_p3
//
//  Created by Buddha G on 8/2/14.
//  Copyright (c) 2014 Summer_2014_CS32. All rights reserved.
//

#ifndef __Tetris_p3__Pieces__
#define __Tetris_p3__Pieces__

#include <iostream>

class Pieces
{
public:
    
    int GetBlockType (int pPiece, int pRotation, int pX, int pY);
    int GetXInitialPosition (int pPiece, int pRotation);
    int GetYInitialPosition (int pPiece, int pRotation);
};

#endif /* defined(__Tetris_p3__Pieces__) */
