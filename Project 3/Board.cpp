#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>

using namespace std;

class BoardImpl
{
  public:
    BoardImpl(const Game& g);
    ~BoardImpl();
    void clear();
    void block();
    void unblock();
    bool placeShip(Point topOrLeft, int shipId, Direction dir);
    bool unplaceShip(Point topOrLeft, int shipId, Direction dir);
    void display(bool shotsOnly) const;
    bool attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId);
    bool allShipsDestroyed() const;
  private:
    char** m_cpBoard;
    const Game& m_game;
};

BoardImpl::BoardImpl(const Game& g) : m_game(g)
{
    m_cpBoard = new char*[m_game.rows()]; //create rows

    for(int i = 0; i < m_game.rows(); i++)
        m_cpBoard[i] = new char[m_game.cols()]; //create col for each row

    clear(); // initialize the board.
}

BoardImpl::~BoardImpl()
{
    for(int i = 0; i < m_game.rows(); i++)
          delete [] m_cpBoard[i]; //delete [#cols] for each [#i] row.
    delete [] m_cpBoard; //delete [#rows]
}

void BoardImpl::clear()
{
    for(int r = 0; r< m_game.rows(); r++)
        for(int c = 0; c< m_game.cols(); c++)
            m_cpBoard[r][c] = '.';
}

void BoardImpl::block()
{
      // Block cells with 50% probability
    for (int r = 0; r < m_game.rows(); r++)
        for (int c = 0; c < m_game.cols(); c++)
            if (randInt(2) == 0)
          //if(c == 5 || c == 6 || c == 7 || c==8 || c==9)
                m_cpBoard[r][c] = 'X' ; // TODO:  Replace this with code to block cell (r,c)
}

void BoardImpl::unblock()
{
    for (int r = 0; r < m_game.rows(); r++)
        for (int c = 0; c < m_game.cols(); c++)
            if(m_cpBoard[r][c] == 'X')
            {
                m_cpBoard[r][c] = '.'; // TODO:  Replace this with code to unblock cell (r,c) if blocked
            }
}

//returns false if cannot place.
bool BoardImpl::placeShip(Point topOrLeft, int shipId, Direction dir)
{
   if(shipId < 0 || shipId >= m_game.nShips()) //if true, ship doesn't exist
        return false; // This compiles, but may not be correct

    int nLength = m_game.shipLength(shipId);
    char cShipSymbol = m_game.shipSymbol(shipId);

    //Valid topOrLeft coordinate?
    if(topOrLeft.r < 0 || topOrLeft.r >= m_game.rows() ||
        topOrLeft.c < 0 || topOrLeft.c >= m_game.cols())
        return false;

    //Too long
    if(dir == HORIZONTAL && (topOrLeft.c + nLength) > m_game.cols())
        return false;

    //Too long
    if(dir == VERTICAL && (topOrLeft.r + nLength) > m_game.rows())
        return false;

    //If space occupied by something else. besides '.' then return false
    if(dir == HORIZONTAL)
    {
        for(int i = topOrLeft.c; i < topOrLeft.c + nLength; i++)
        {
            if(m_cpBoard[topOrLeft.r][i] != '.')
                return false;
        }
    }
    else if(dir == VERTICAL)//if occupied by something besides '.'
    {
         for(int i = topOrLeft.r; i < topOrLeft.r + nLength; i++)
        {
            if(m_cpBoard[i][topOrLeft.c] != '.')
                return false;
        }       
    }

    //check if symbol already exists in map.
    for(int r = 0; r< m_game.rows(); r++)
    {
        for(int c = 0; c < m_game.cols(); c++)
        {
            if(m_cpBoard[r][c] == cShipSymbol)
                return false;
        }
    }

    /********************** END OF FALSE CONDITIONS ********************/

    //if it makes this far, should return true.
    if(dir == HORIZONTAL)
    {
        for(int i = topOrLeft.c; i < topOrLeft.c + nLength; i++)
            m_cpBoard[topOrLeft.r][i] = cShipSymbol;
    }
    if(dir == VERTICAL)
    {
        for(int i = topOrLeft.r; i < topOrLeft.r + nLength; i++)
            m_cpBoard[i][topOrLeft.c] = cShipSymbol;
    }

    //NEED TO ADD FUNCTIONALITY OF CHECKING WHETHER IT WAS PLACED AND NEVER UNPLACED
    //CAN ONLY BE IN THERE ONCE.
    //ALSO WHETHER THE SPOT IS BLOCKED.
    return true;
}

bool BoardImpl::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    //NEED TO CHECK IF WE GO OUT OF BOUNDS!!! for ADDSHIP TOO!!!!
    //ALSO CHECK IF DIR IS WRONG.
    if(shipId < 0 || shipId >= m_game.nShips())//if true, wrong id.
        return false; // This compiles, but may not be correct

    if(dir != HORIZONTAL && dir != VERTICAL) //invalid direction
        return false;

    int nShipLength = m_game.shipLength(shipId);
    char cShipSymbol = m_game.shipSymbol(shipId);

    //if-else block: if not the whole ship.
    if(dir == HORIZONTAL)
    {
        if(topOrLeft.c + nShipLength > m_game.cols()) //ship is too long.
            return false;
        for(int i = topOrLeft.c; i < topOrLeft.c + nShipLength; i++)
            if(m_cpBoard[topOrLeft.r][i] != cShipSymbol)
                return false;
    }
    else if(dir == VERTICAL)
    {
        if(topOrLeft.r + nShipLength > m_game.rows()) //if ship is too long
            return false;
        for(int i = topOrLeft.r; i < topOrLeft.r + nShipLength; i++)
            if(m_cpBoard[i][topOrLeft.c] != cShipSymbol)
                return false;
    }//end if-else

    //if it gets here. then good it SHOULD return true at some point.
    if(dir == HORIZONTAL)
    {
        for(int i = topOrLeft.c; i < topOrLeft.c + nShipLength; i++)
            m_cpBoard[topOrLeft.r][i] = '.';
    }
    else if(dir == VERTICAL)
    {
        for(int i = topOrLeft.r; i < topOrLeft.r + nShipLength; i++)
            m_cpBoard[i][topOrLeft.c] = '.';
    }
    return true;
}

void BoardImpl::display(bool shotsOnly) const
{//Shouldn't display not change anything. Let attack deal with changing image
    // of the board
    cout << "  ";//two spaces
    for(int c = 0; c < m_game.cols(); c++)
        cout << c;//each column element is printed.
    cout << endl;//new line
    for(int r = 0; r < m_game.rows(); r++)//each row is being printed.
    {
        cout << r << " ";
        for(int c = 0; c < m_game.cols(); c++)
        {
            if(shotsOnly == false)
                cout << m_cpBoard[r][c]; //PRINT EVERYTHING!!!!
            else
            {
                if(m_cpBoard[r][c] != '.' && m_cpBoard[r][c] != 'o' && m_cpBoard[r][c] != 'X')
                    cout << '.';
                else
                    cout << m_cpBoard[r][c];//PRINT NORMALLY.
            }
        }
        cout << endl; //GET READY FOR NEXT ROW
    }
   cout << endl; // This compiles, but may not be correct
}

bool BoardImpl::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    if(p.r < 0 || p.r >= m_game.rows() || p.c < 0 || p.c >= m_game.cols())
        return false;

    //Already marked this square. should return false.
    if(m_cpBoard[p.r][p.c] == 'X' || m_cpBoard[p.r][p.c] == 'o')
        return false; // This compiles, but may not be correct

    char cShipSymbol = ' '; //conditions for X and o have already been checked.
    if(m_cpBoard[p.r][p.c] != '.')
    {
        cShipSymbol = m_cpBoard[p.r][p.c];
        m_cpBoard[p.r][p.c] = 'X';
        shotHit = true;
    }
    else if(m_cpBoard[p.r][p.c] == '.')
    {
        m_cpBoard[p.r][p.c] = 'o';
        shotHit = false;
    }

    shipDestroyed = false;//should be set to false first.
    //check if symbol still exists in map.
    if(cShipSymbol != ' ' && m_cpBoard[p.r][p.c] != '.')
    {
    shipDestroyed = true; //first true. until proven false.
        for(int r = 0; r< m_game.rows() && shipDestroyed; r++)
        {
            for(int c = 0; c < m_game.cols(); c++)
            {
                if(m_cpBoard[r][c] == cShipSymbol)
                {
                    shipDestroyed = false;
                    break;
                }
            }
        }
    }

    //what if ship destroyed is already false?
    if(shipDestroyed)
    {
        for(int i = 0; i < m_game.nShips(); i++)
        {
          char cTempSym = m_game.shipSymbol(i);
          if(cTempSym == cShipSymbol)
                shipId = i;
        }
    }
    //how can i find out whether or not the whole ship is destroyed.
    //find the shipid correlating to the ship symbol. check if the symbol 
    return true;
}

bool BoardImpl::allShipsDestroyed() const
{
    for(int r = 0; r < m_game.rows(); r++)
    {
        for(int c = 0; c < m_game.cols(); c++)
        {
          if(m_cpBoard[r][c] != '.' && m_cpBoard[r][c] != 'o' && m_cpBoard[r][c] != 'X')
                return false;
        }
    }
    return true; // This compiles, but may not be correct
}

//******************** Board functions ********************************

// These functions simply delegate to BoardImpl's functions.
// You probably don't want to change any of this code.

Board::Board(const Game& g)
{
    m_impl = new BoardImpl(g);
}

Board::~Board()
{
    delete m_impl;
}

void Board::clear()
{
    m_impl->clear();
}

void Board::block()
{
    return m_impl->block();
}

void Board::unblock()
{
    return m_impl->unblock();
}

bool Board::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->placeShip(topOrLeft, shipId, dir);
}

bool Board::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->unplaceShip(topOrLeft, shipId, dir);
}

void Board::display(bool shotsOnly) const
{
    m_impl->display(shotsOnly);
}

bool Board::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    return m_impl->attack(p, shotHit, shipDestroyed, shipId);
}

bool Board::allShipsDestroyed() const
{
    return m_impl->allShipsDestroyed();
}