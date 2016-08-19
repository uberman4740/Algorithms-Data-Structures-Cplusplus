#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <vector>
using namespace std;

class Ship
{
  public:
    int nGetShipId()        const { return m_nShipId;}
    int nGetShipLength()    const { return m_nShipLength; }
    char nGetShipSymbol()   const { return m_cShipSymbol; }
    string nGetShipName()   const { return m_sShipName; }
    Ship(int nLength, string sName, char cSymbol, int shipId);
  private:
    char m_cShipSymbol;
    string m_sShipName;
    int m_nShipLength;
    int m_nShipId;
};

Ship::Ship(int nLength, string sName, char cSymbol, int shipId)
    : m_cShipSymbol(cSymbol), m_nShipLength(nLength), m_sShipName(sName),
     m_nShipId(shipId)
    {}

class GameImpl
{
  public:
    GameImpl(int nRows, int nCols);
    ~GameImpl();
    int rows() const;
    int cols() const;
    bool isValid(Point p) const;
    Point randomPoint() const;
    bool addShip(int length, char symbol, string name);
    int nShips() const;
    int shipLength(int shipId) const;
    char shipSymbol(int shipId) const;
    string shipName(int shipId) const;
    bool checkShipRedun(char cSymbol) const;
    Player* play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause);
  private:
    int m_nShipCount;
    int m_nRows;
    int m_nCols;
    vector<Ship> m_vShips;
};

void waitForEnter()
{
    cout << "Press enter to continue: ";
    cin.ignore(10000, '\n');
}

/************************ GAME IMPLEMENTATION *************/
GameImpl::GameImpl(int nRows, int nCols)
 : m_nShipCount(0), m_nRows(nRows), m_nCols(nCols)
{
    if(nRows <= 0 || nRows > MAXROWS || nCols <= 0 || nCols > MAXCOLS)
        exit(1); //invariants.
}

GameImpl::~GameImpl()
{
    m_vShips.clear();
}

//return the number of rows in gameboard.
int GameImpl::rows() const
{
    return m_nRows;  // This compiles but may not be correct
}

//return the number of columns in gameboard.
int GameImpl::cols() const
{
    return m_nCols;  // This compiles but may not be correct
}

bool GameImpl::isValid(Point p) const
{
    return p.r >= 0  &&  p.r < rows()  &&  p.c >= 0  &&  p.c < cols();
}

Point GameImpl::randomPoint() const
{
    return Point(randInt(rows()), randInt(cols()));
}

//returns true if symbol exists already.
bool GameImpl::checkShipRedun(char cSymbol) const
{
    vector<Ship>::const_iterator it;
    for(it = m_vShips.begin(); it != m_vShips.end(); it++)
    {
        if(it->nGetShipSymbol() == cSymbol)//if symbol matches an existing one;
            return true;
    }
    return false;
}

bool GameImpl::addShip(int length, char symbol, string name)
{
    if(length <=0) //ship length is not positive.
      return false;  // This compiles but may not be correct

    if(symbol == 'X' || symbol == 'o' || symbol == '.')
        return false;

    if(checkShipRedun(symbol))
        return false;

    m_vShips.push_back(Ship(length, name, symbol, m_nShipCount));
    m_nShipCount++;
    return true;
}

vector<Ship>::const_iterator iterate(const vector<Ship>& vShip, const int shipId)
{
    vector<Ship>::const_iterator it;
    for(it = vShip.begin(); it != vShip.end(); it++)
    {
        if(shipId == it->nGetShipId())
            break;
    }
    return it;
}

int GameImpl::nShips() const
{
    return m_nShipCount;  // This compiles but may not be correct
}

int GameImpl::shipLength(int shipId) const
{
    vector<Ship>::const_iterator it = iterate(m_vShips, shipId);
    //for(it = m_vShips.begin(); it != m_vShips.end() || shipId != it->nGetShipId; it++);
    if(it != m_vShips.end())     
        return it->nGetShipLength();  // This compiles but may not be correct
    else
        return -1; //what value should it be if ship not found?
}

char GameImpl::shipSymbol(int shipId) const
{
    vector<Ship>::const_iterator it = iterate(m_vShips, shipId);
    if(it != m_vShips.end())
        return it->nGetShipSymbol();
    else
        return '?';  // This compiles but may not be correct
}

string GameImpl::shipName(int shipId) const
{
    vector<Ship>::const_iterator it = iterate(m_vShips, shipId);
    if(it != m_vShips.end())
        return it->nGetShipName();
    else
        return "";  // This compiles but may not be correct
}

Player* GameImpl::play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause)
{
    bool bCheck;
    int nCounter = 0;

    do{
        bCheck = p1->placeShips(b1);
        if(!bCheck)
        {
            b1.clear();
            nCounter++;
        }
    }while(!bCheck && nCounter < MAX_PLACEMENT_TRIES);

    if(nCounter == 50)
        return NULL;
    nCounter = 0;
    do{
        bCheck = p2->placeShips(b2);
        if(!bCheck)
        {
            b2.clear();
            nCounter++;
        }
    }while(!bCheck && nCounter < MAX_PLACEMENT_TRIES);

    if(nCounter == 50)
        return NULL;
    bool isHuman1 = p1->isHuman();
    bool isHuman2 = p2->isHuman();
    bool shotHit;
    bool shipDestroyed;
    int shipId;
    bool validShot;

    //while one of them is not all destroyed.
    while(!(b1.allShipsDestroyed() || b2.allShipsDestroyed()))
        {
            cout << p1->name() << " turn. Board for " << p2->name() << ": " << endl;
            b2.display(isHuman1);

            //first player attacks BOARD2. display board2.
            Point cP1 = p1->recommendAttack();
            validShot = b2.attack(cP1, shotHit, shipDestroyed, shipId);
            p1->recordAttackResult(cP1, validShot, shotHit, shipDestroyed, shipId);//p1 accumulating data.
            cout << p1->name();
            
            if(!validShot)
                cout << " wasted a shot at (" << cP1.r << "," << cP1.c <<")." << endl;
            
            if(validShot)
            {
                cout << " attacked (" << cP1.r << "," << cP1.c << ") and ";
                if(shotHit && !shipDestroyed)
                    cout << "hit something, ";
                else if(!(shotHit || shipDestroyed))
                    cout << "missed, ";
                else if(shotHit && shipDestroyed)
                    cout << "destroyed the " << p2->game().shipName(shipId) << " ";
            }
            cout << "resulting in: " << endl;
            b2.display(isHuman1);
            if(shouldPause)
              waitForEnter();
            if(b2.allShipsDestroyed())
                break;

            //second player attacks BOARD1. display board1.
            cout << p2->name() << " turn. Board for " << p1->name() << ": " << endl;
            b1.display(isHuman2);
            Point cP2 = p2->recommendAttack();
            validShot = b1.attack(cP2, shotHit, shipDestroyed, shipId);
            p2->recordAttackResult(cP2, validShot, shotHit, shipDestroyed, shipId);

            cout << p2->name();
            
            if(!validShot)
                cout << " wasted a shot at (" << cP2.r << "," << cP2.c <<")." << endl;
            
            if(validShot)
            {
                cout << " attacked (" << cP2.r << "," << cP2.c << ") and ";
                if(shotHit && !shipDestroyed)
                    cout << "hit something, ";
                else if(!(shotHit || shipDestroyed))
                    cout << "missed, ";
                else if(shotHit && shipDestroyed)
                    cout << "destroyed the " << p1->game().shipName(shipId) << " ";
            }
            cout << "resulting in: " << endl;
            b1.display(isHuman2);
            if(shouldPause)
                waitForEnter();
        }

    if(b1.allShipsDestroyed())
    {
        cout << p2->name() << " wins!" << endl;
        cout << "Winner's board:" << endl;
        b2.display(false);
    }
    else if(b2.allShipsDestroyed())
    {
        cout << p1->name() << " wins!" << endl;
        cout << "Winner's board:" << endl;
        b1.display(false);
    }

    if(b1.allShipsDestroyed())
        return p2;
    else
        return p1;
}

//******************** Game functions *******************************

// These functions for the most part simply delegate to GameImpl's functions.
// You probably don't want to change any of the code from this point down.

Game::Game(int nRows, int nCols)
{
    if (nRows < 1  ||  nRows > MAXROWS)
    {
        cout << "Number of rows must be >= 1 and <= " << MAXROWS << endl;
        exit(1);
    }
    if (nCols < 1  ||  nCols > MAXCOLS)
    {
        cout << "Number of columns must be >= 1 and <= " << MAXCOLS << endl;
        exit(1);
    }
    m_impl = new GameImpl(nRows, nCols);
}

Game::~Game()
{
    delete m_impl;
}

int Game::rows() const
{
    return m_impl->rows();
}

int Game::cols() const
{
    return m_impl->cols();
}

bool Game::isValid(Point p) const
{
    return m_impl->isValid(p);
}

Point Game::randomPoint() const
{
    return m_impl->randomPoint();
}

bool Game::addShip(int length, char symbol, string name)
{
    if (length < 1)
    {
        cout << "Bad ship length " << length << "; it must be >= 1" << endl;
        return false;
    }
    if (length > rows()  &&  length > cols())
    {
        cout << "Bad ship length " << length << "; it won't fit on the board"
             << endl;
        return false;
    }
    if (!isascii(symbol)  ||  !isprint(symbol))
    {
        cout << "Unprintable character with decimal value " << symbol
             << " must not be used as a ship symbol" << endl;
        return false;
    }
    if (symbol == 'X'  ||  symbol == '.'  ||  symbol == 'o')
    {
        cout << "Character " << symbol << " must not be used as a ship symbol"
             << endl;
        return false;
    }
    int totalOfLengths = 0;
    for (int s = 0; s < nShips(); s++)
    {
        totalOfLengths += shipLength(s);
        if (shipSymbol(s) == symbol)
        {
            cout << "Ship symbol " << symbol
                 << " must not be used for more than one ship" << endl;
            return false;
        }
    }
    if (totalOfLengths + length > rows() * cols())
    {
        cout << "Board is too small to fit all ships" << endl;
        return false;
    }
    return m_impl->addShip(length, symbol, name);
}

int Game::nShips() const
{
    return m_impl->nShips();
}

int Game::shipLength(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipLength(shipId);
}

char Game::shipSymbol(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipSymbol(shipId);
}

string Game::shipName(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipName(shipId);
}

Player* Game::play(Player* p1, Player* p2, bool shouldPause)
{
    if (p1 == NULL  ||  p2 == NULL  ||  nShips() == 0)
        return NULL;
    Board b1(*this);
    Board b2(*this);
    return m_impl->play(p1, p2, b1, b2, shouldPause);
}