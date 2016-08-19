//
//  Pieces.cpp
//  Tetris_p3
//
//  Created by Buddha G on 8/2/14.
//  Copyright (c) 2014 Summer_2014_CS32. All rights reserved.
//

#include "Pieces.h"
char mPieces [7][4][4][4]=// [number of pieces][no. of rotations][block size vertical][block size horiz]

{    // O PIECE
    {
        
    
        //ROTATATION 0
        {
            {2,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        //ROTATATION 1
       
        {
            {2,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
       //ROTATATION 2
        {
            {2,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
      //ROTATATION 3
        {
            {2,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        }
    },
    
  // I PIECE
    {
        
        //ROTATATION 0
        {
            {0,0,0,0},
            {1,2,1,1},
            {0,0,0,0},
            {0,0,0,0}
        },
        //ROTATATION 1
        
        {
            {0,1,0,0},
            {0,2,0,0},
            {0,1,0,0},
            {0,1,0,0}
        },
        //ROTATATION 2
        {
            {0,0,0,0},
            {1,2,1,1},
            {0,0,0,0},
            {0,0,0,0}
        },
        //ROTATATION 3
        {
            {0,1,0,0},
            {0,2,0,0},
            {0,1,0,0},
            {0,1,0,0}
        }

        
    },
    
    // L PIECE
    {
        //ROTATATION 0
        {
            {0,0,0,0},
            {1,1,1,0},
            {1,0,0,0},
            {0,0,0,0}
        },
        //ROTATATION 1
        
        {
            {0,1,1,0},
            {0,0,1,0},
            {0,0,1,0},
            {0,0,0,0}
        },
        //ROTATATION 2
        {
            {0,0,0,0},
            {0,0,1,0},
            {1,1,1,0},
            {0,0,0,0}
        },
        //ROTATATION 3
        {
            {0,0,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,1,0}
        }
        
        
    },
    
    // J PIECE
    {
        //ROTATATION 1
        {
            {0,0,0,0},
            {0,1,1,1},
            {0,0,0,1},
            {0,0,0,0}
        },
        //ROTATATION 1
        
        {
            {0,0,0,0},
            {0,0,1,0},
            {0,0,1,0},
            {0,1,1,0}
        },
        //ROTATATION 1
        {
            {0,0,0,0},
            {0,1,0,0},
            {0,1,1,1},
            {0,0,0,0}
        },
        //ROTATATION 1
        {
            {0,1,1,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        }
        
        
    },
    
    // Z PIECE  (CHECK IT IN SPEC)
    {
        //ROTATATION 1
        {
            {0,0,0,0},
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        //ROTATATION 1
        
        {
            {0,0,1,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        //ROTATATION 1
        {
            {0,0,0,0},
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        //ROTATATION 1
        {
            {0,0,1,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        }
        
        
    },

    // S PIECE
    {
        //ROTATATION 1
        {
            {0,0,0,0},
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0}
        },
        //ROTATATION 1
        
        {
            {0,1,0,0},
            {0,1,1,0},
            {0,0,1,0},
            {0,0,0,0}
        },
        //ROTATATION 1
        {
            {0,0,0,0},
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0}
        },
        //ROTATATION 1
        {
            {0,1,0,0},
            {0,1,1,0},
            {0,0,1,0},
            {0,0,0,0}
        }
        
        
    },
    
    // T PIECE
    {
        //ROTATATION 1
        {
            {0,1,0,0},
            {1,2,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        //ROTATATION 1
        
        {
            {0,1,0,0},
            {0,2,1,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        //ROTATATION 1
        {
            {2,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        //ROTATATION 1
        {
            {0,1,0,0},
            {1,2,0,0},
            {0,1,0,0},
            {0,0,0,0}
        }
        
        
    }
};


int mPieces_initialPosition [7][4][2] =
{
    
    // O PIECE
    {
        {3,0},
        {3,0},
        {3,0},
        {3,0}
    },
    
    
    // I PIECE
    {
        {3,0},
        {3,0},
        {3,0},
        {3,0}
    },
    
    // L PIECE
    {
        {3,0},
        {3,0},
        {3,0},
        {3,0}
    },
    
    // J PIECE
    {
        {3,0},
        {3,0},
        {3,0},
        {3,0}
    },
    
    // Z PIECE  (CHECK IT IN SPEC)
    {
        {3,0},
        {3,0},
        {3,0},
        {3,0}
    },
    
    // S PIECE
    {
        {3,0},
        {3,0},
        {3,0},
        {3,0}
    },
    
    // T PIECE
    {
        {3,0},
        {3,0},
        {3,0},
        {3,0}
    },
};


/*
 ======================================
 Return the type of a block (0 = no-block, 1 = normal block, 2 = pivot block)
 
 Parameters:
 
 >> piece_to_draw:        Piece to draw
 >> pRotation: 1 of the 4 possible rotations
 >> pX:            Horizontal position in blocks
 >> pY:            Vertical position in blocks
 ======================================
 */
int Pieces::GetBlockType (int piece_to_draw, int pRotation, int pX, int pY)
{
    return mPieces [piece_to_draw][pRotation][pX][pY];
}


/*
 ======================================
 Returns the horizontal displacement of the piece that has to be applied in order to create it in the
 correct position.
 
 Parameters:
 
 >> piece_to_draw:    Piece to draw
 >> pRotation: 1 of the 4 possible rotations
 ======================================
 */
int Pieces::GetXInitialPosition (int piece_to_draw, int pRotation)
{
    return mPieces_initialPosition  [piece_to_draw][pRotation][0];
}


/*
 ======================================
 Returns the vertical displacement of the piece that has to be applied in order to create it in the
 correct position.
 
 Parameters:
 
 >> piece_to_draw:    Piece to draw
 >> pRotation: 1 of the 4 possible rotations
 ======================================
 */
int Pieces::GetYInitialPosition (int piece_to_draw, int pRotation)
{
    return mPieces_initialPosition  [piece_to_draw][pRotation][1];
}
