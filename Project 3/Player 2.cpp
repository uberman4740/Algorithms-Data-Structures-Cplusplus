#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include <stack>
using namespace std;

 //*********************************************************************
 //  AwfulPlayer
 //*********************************************************************

 class AwfulPlayer : public Player
 {
   public:
     AwfulPlayer(string nm, const Game& g);
     virtual bool placeShips(Board& b);
     virtual Point recommendAttack();
     virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                                 bool shipDestroyed, int shipId);
   private:
     Point m_lastCellAttacked;
 };

 AwfulPlayer::AwfulPlayer(string nm, const Game& g)
  : Player(nm, g), m_lastCellAttacked(0, 0)
 {}

 bool AwfulPlayer::placeShips(Board& b)
 {
       // Clustering ships is bad strategy
     for (int k = 0; k < game().nShips(); k++)
         if ( ! b.placeShip(Point(k,0), k, HORIZONTAL))
             return false;
     return true;
 }

 Point AwfulPlayer::recommendAttack()
 {
     if (m_lastCellAttacked.c > 0)
         m_lastCellAttacked.c--;
     else
     {
         m_lastCellAttacked.c = game().cols() - 1;
         if (m_lastCellAttacked.r > 0)
             m_lastCellAttacked.r--;
         else
             m_lastCellAttacked.r = game().rows() - 1;
     }
     return m_lastCellAttacked;
 }

 void AwfulPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
                                      bool /* shotHit */, bool /* shipDestroyed */,
                                      int /* shipId */)
 {
       // AwfulPlayer completely ignores the result of any attack
 }

//*********************************************************************
//  HumanPlayer
//*********************************************************************

bool getLineWithTwoIntegers(int& r, int& c)
{
    bool result = (cin >> r >> c);
    if (!result)
        cin.clear();  // clear error state so can do more input operations
    cin.ignore(10000, '\n');
    return result;
}

// TODO:  You need to replace this with a real class declaration and
//        implementation.
//typedef AwfulPlayer HumanPlayer;

class HumanPlayer : public Player
{
  public:
      virtual bool isHuman() const { return true; }
      HumanPlayer(string nm,  const Game& g);
      virtual bool placeShips(Board& b);
      Point recommendAttack();
      void recordAttackResult(Point p, bool validShot, bool shotHit,
                                        bool shipDestroyed, int shipId);
  private:
};

HumanPlayer::HumanPlayer(string nm, const Game&g) : Player(nm, g){}

Point HumanPlayer::recommendAttack()
{
  int r, c;
  cout << "Enter the row and column to attack (e.g. 3 5): ";
  getLineWithTwoIntegers(r, c);
  return Point(r, c);
}

void HumanPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
                                      bool /* shotHit */, bool /* shipDestroyed */,
                                      int /* shipId */)
{}

bool HumanPlayer::placeShips(Board& b)
{
  Point p;
  string direction;
  Direction dir;
  for(int i = 0; i < game().nShips(); i++)
  { 
  cout << endl;
    b.display(false);
    bool bChecker = false;
    do{

    cout << "Enter h or v for direction of " << game().shipName(i) <<
    " (length " << game().shipLength(i) << "): ";
    cin >> direction;

    if(direction[0] == 'h')
      dir = HORIZONTAL;
    else if(direction[0] == 'v')
      dir = VERTICAL;
    else
      cout << "Direction must be h or v." << endl;
    }while(direction[0] != 'v' && direction[0] != 'h');

    do{
      cout << "Enter row and column of leftmost cell (e.g. 3 5): ";
        
      getLineWithTwoIntegers(p.r, p.c);

      bChecker = b.placeShip(p, i, dir);
    
      if(!bChecker)
        cout << "The ship cannot be placed there." << endl;
    }while(!bChecker || (p.r < 0 || p.r > game().rows() || p.c < 0 || p.c > game().rows()));
  }

  if(game().nShips() > 0)
    b.display(false);
  return true;
}

//*********************************************************************
//  MediocrePlayer
//*********************************************************************

// TODO:  You need to replace this with a real class declaration and
//        implementation.
//typedef AwfulPlayer MediocrePlayer;

class MediocrePlayer : public Player
{
  public:
    MediocrePlayer(string nm, const Game& g);
    ~MediocrePlayer();
    bool placeShips(Board& b);
    bool placingShips(Board& b, Point newPoint, int nNumShips);
    void attack();
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                        bool shipDestroyed, int shipId);
  private:
    char** m_cpMarks;
    int m_nRows;
    int m_nCols;
    int m_nState;
};

MediocrePlayer::MediocrePlayer(string nm, const Game& g)
 : Player(nm, g), m_nRows(game().rows()), m_nCols(game().cols()), m_nState(1)
{
  m_cpMarks = new char*[m_nRows];
  for(int i =0; i < m_nRows; i++)
     m_cpMarks[i] = new char[m_nCols];

   for(int r = 0; r < m_nRows; r++)
    for(int c = 0; c < m_nCols; c++)
      m_cpMarks[r][c] = '.';
}

MediocrePlayer::~MediocrePlayer()
{
  for(int i =0; i < m_nRows; i++)
    delete [] m_cpMarks[i];

  delete [] m_cpMarks;
}

bool MediocrePlayer::placeShips(Board& b)
{
  b.block(); //block the cells with #.
  //check to make sure it is placeable after block() function
  bool bCheck = placingShips(b, Point(0,0), game().nShips());

  b.unblock();
  return bCheck;
}

bool MediocrePlayer::placingShips(Board& b, Point newPoint, int nNumOfShips)
{
  if(newPoint.r == m_nRows-1 && newPoint.c == m_nCols-1)
    return false;//use this false to unblock previous ship!
  //if no more ships
  if(nNumOfShips <= 0)
    return true;

  //bChecker1 says if you cannot place it HORIZONTALLY. THEN GO TRY VERTICALLY
  bool bChecker1 = b.placeShip(newPoint, nNumOfShips-1, HORIZONTAL);

  if(bChecker1 && newPoint.c+1 == m_nCols)
  return placingShips(b, Point(newPoint.r+1, 0), nNumOfShips-1);
  else if(bChecker1)
    return placingShips(b, Point(newPoint.r, newPoint.c+1), nNumOfShips-1);
  else
  {
    bChecker1 = b.placeShip(newPoint, nNumOfShips-1, VERTICAL);
    if(!bChecker1)
    {
        //recursion call with new point, but same number of ships.
      if(newPoint.c + 1 == m_nCols)
        return placingShips(b, Point(newPoint.r+1, 0), nNumOfShips);
      else
        return placingShips(b, Point(newPoint.r, newPoint.c + 1), nNumOfShips);
    }
    else if(bChecker1 && newPoint.c + 1 == m_nCols)
       return placingShips(b, Point(newPoint.r+1, 0), nNumOfShips-1);
    else
       return placingShips(b, Point(newPoint.r, newPoint.c+1), nNumOfShips-1);
  }
}

void MediocrePlayer::recordAttackResult(Point p, bool validShot, bool shotHit,
                                          bool shipDestroyed, int shipId)
{
  if(validShot)//if its a valid shot
  {
    if(shotHit)//and it hits a ship
    {
      m_nState = 2;//if it hits a ship.stay in state 2
      m_cpMarks[p.r][p.c] = 'X';//change it to hit on our marked map.
      if(shipDestroyed)//and it destroys the ship
      {
        for(int r=0; r < m_nRows; r++)//remove all + from marked map.
        {
          for(int c=0; c < m_nCols; c++)
          {
            if(m_cpMarks[r][c] == '+')
              m_cpMarks[r][c] = '.';
            else if(m_cpMarks[r][c] == 'S')
              m_cpMarks[r][c] = 'X';
          }
        }
        m_nState = 1;//return state to 1.
      }
    }
    else
      m_cpMarks[p.r][p.c] = 'o';
  }

  char cSExist = ' ';//init to space
  if(m_nState == 2)
  {
    for(int r = 0; r < m_nRows; r++)
    {
      for(int c = 0; c < m_nRows; c++)
        if(m_cpMarks[r][c] == 'S')
          cSExist = 'S';
    }
  }

  if(cSExist != 'S' && m_nState == 2)//if S does not exist. THEN MAKE THE +.
  {
    int nRow = p.r;
    int nCol = p.c;
    m_cpMarks[p.r][p.c] = 'S';
      for(int r = nRow+1; r < nRow + 5; r++)
        if(r < m_nRows && m_cpMarks[r][nCol] != 'o' && m_cpMarks[r][nCol] != 'X')
          m_cpMarks[r][nCol] = '+';
      for(int r = nRow-1; r > nRow - 5; r--)
        if(r >= 0 && m_cpMarks[r][nCol] != 'o' && m_cpMarks[r][nCol] != 'X')
          m_cpMarks[r][nCol] = '+';
      for(int c = nCol+1; c < nCol + 5; c++)
        if(c < m_nCols && m_cpMarks[nRow][c] != 'o' && m_cpMarks[nRow][c] != 'X')
          m_cpMarks[nRow][c] = '+';
      for(int c = nCol-1; c > nCol -5; c--)
        if(c >= 0 && m_cpMarks[nRow][c] != 'o' && m_cpMarks[nRow][c] != 'X')
          m_cpMarks[nRow][c] = '+';
    }
}

Point MediocrePlayer::recommendAttack()
{
  if(m_nState == 1)
  {
  do{
    int rand1 = rand() % m_nRows;
    int rand2 = rand() % m_nCols;
      if(m_cpMarks[rand1][rand2] != 'X' && m_cpMarks[rand1][rand2] != 'o')
        return Point(rand1,rand2);
  }while(true);
  }
  else if(m_nState == 2)//find where the + exists.
  {
    for(int r=0; r < m_nRows; r++)
    {
      for(int c=0; c < m_nCols; c++)
        if(m_cpMarks[r][c] == '+')
          return Point(r,c);
    }
  }
  return Point(0,0);//should never even reach this point
}

//*********************************************************************
//  GoodPlayer
//*********************************************************************
class GoodPlayer : public Player
{
  public:
    virtual ~GoodPlayer();
    GoodPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    bool placingShipsReverse(Board& b, Point newPoint, int nNumOfShips, int nEndPoint);
    bool placingShips(Board& b, Point newPoint, int nNumShips);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                        bool shipDestroyed, int shipId);
  private:
    char** m_cpMarks;//create own map of game
    int m_nRows;//total rows
    int m_nCols;//total columns
    int m_nState;//2 states
    stack<Point> m_qRight;
    stack<Point> m_qTop;
    stack<Point> m_qBot;
    stack<Point> m_qLeft;
    int m_nTotalX;
  int m_nXCounter;
    Point m_lastCellAttacked;
    Point m_sCenterPoint;//focal point
};

GoodPlayer::GoodPlayer(string nm, const Game& g) : Player(nm, g), m_nRows(game().rows()),
    m_nCols(game().cols()), m_nState(1), m_sCenterPoint(-1,-1), m_lastCellAttacked(-1,-1)
{
  m_nTotalX = 0;
  m_nXCounter = 0;
  m_cpMarks = new char*[m_nRows];
  
  for(int i=0; i< m_nRows; i++)
    m_cpMarks[i] = new char[m_nCols];

  //initialize board;
  for(int r=0; r < m_nRows; r++)
    for(int c=0; c< m_nCols; c++)
      m_cpMarks[r][c] = '.';
}

GoodPlayer::~GoodPlayer()
{
  for(int i=0; i < m_nRows; i++)
    delete [] m_cpMarks[i];

  delete[] m_cpMarks;
}

bool GoodPlayer::placeShips(Board& b)
{
  b.block();
  int nBeginHalf = (game().nShips())/2;
  int nEndHalf = game().nShips() - nBeginHalf;
  bool bCheck1 = placingShips(b, Point(0,0), nBeginHalf);
  bool bCheck2 = placingShipsReverse(b, Point(9,9), game().nShips(), nEndHalf); //long ships at bottom
  b.unblock();

  return (bCheck1 && bCheck2);
}


bool GoodPlayer::placingShips(Board& b, Point newPoint, int nNumOfShips)
{
  //hitting last square.
  if(newPoint.r >= m_nRows-1 || newPoint.c >= m_nCols-1)
    return false;

  //if no more ships
  if(nNumOfShips <= 0)
    return true;

  //bChecker1 says if you cannot place it VERTICAL, then HORIZONTAL
  bool bChecker1 = b.placeShip(newPoint, nNumOfShips-1, VERTICAL);

  if(bChecker1 && newPoint.c+2 >= m_nCols)//go up two columns
    return placingShips(b, Point(newPoint.r+2, 0), nNumOfShips-1);//go up two rows
  else if(bChecker1)//go up two columns
    return placingShips(b, Point(newPoint.r, newPoint.c+2), nNumOfShips-1);
  else//bChecker1 is false.
  {
    bChecker1 = b.placeShip(newPoint, nNumOfShips-1, HORIZONTAL);
    if(!bChecker1)
    {
      //recursion call with new point, but same number of ships.
      if(newPoint.c + 2 >= m_nCols)//NO EDGE SHIPS
        return placingShips(b, Point(newPoint.r+2, 0), nNumOfShips);
      else
        return placingShips(b, Point(newPoint.r, newPoint.c+2), nNumOfShips);
    }
    else if(bChecker1 && newPoint.c+2 >= m_nCols)
        return placingShips(b, Point(newPoint.r+2, 0), nNumOfShips-1);
    else
        return placingShips(b, Point(newPoint.r, newPoint.c+2), nNumOfShips-1);
  }
}

bool GoodPlayer::placingShipsReverse(Board& b, Point newPoint, int nNumOfShips, int nEndPoint)
{
  //if no more ships
  if(nNumOfShips < nEndPoint)
    return true;

  //if last square in block then return false since ships more than 0.
  if(newPoint.r == 0 && newPoint.c == 0)
    return false;//use this false to unblock previous ship!

  //bChecker1 says if you cannot place it VERTICALLY AND HORIZONTALLY
  bool bChecker1 = b.placeShip(newPoint, nNumOfShips-1, HORIZONTAL);

  if(bChecker1 && newPoint.c-1 < 0)
    return placingShipsReverse(b, Point(newPoint.r-1, m_nCols-1), nNumOfShips-1, nEndPoint);
  else if(bChecker1)
    return placingShipsReverse(b, Point(newPoint.r, newPoint.c-1), nNumOfShips-1, nEndPoint);
  else//bChecker1 is false
  {
    bChecker1 = b.placeShip(newPoint, nNumOfShips-1, VERTICAL);
      if(!bChecker1)
      {
        //recursion call with new point, but same number of ships.
        if(newPoint.c -1 < 0)//move to slot (9, one less column)
          return placingShipsReverse(b, Point(newPoint.r-1, m_nCols-1), nNumOfShips, nEndPoint);
        else//(row-1, same column)
          return placingShipsReverse(b, Point(newPoint.r, newPoint.c-1), nNumOfShips, nEndPoint);
      }
      else if(bChecker1 && newPoint.c -1 < 0)
          return placingShipsReverse(b, Point(newPoint.r-1, m_nCols-1), nNumOfShips-1, nEndPoint);
      else
          return placingShipsReverse(b, Point(newPoint.r, newPoint.c-1), nNumOfShips-1, nEndPoint);
  }
}

void GoodPlayer::recordAttackResult(Point p, bool validShot, bool shotHit,
                                          bool shipDestroyed, int shipId)
{
  if(validShot)//if its a valid shot
  {
    m_lastCellAttacked.r = p.r;
    m_lastCellAttacked.c = p.c;
    if(shotHit)//and it hits a ship
    {
      m_cpMarks[p.r][p.c] = 'X';//mark on our map hit.
      m_nXCounter++;
      if(shipDestroyed)//FIRST CHECK IF SHIP DESTROYED
      {
        int nShipLength = game().shipLength(shipId);
        m_nTotalX += nShipLength;
        m_nState = 1;
        m_cpMarks[m_sCenterPoint.r][m_sCenterPoint.c] = 'A';
        int c = p.c;
        int r = p.r;
        if(c > m_sCenterPoint.c)//to the right
        {
          while(c != m_sCenterPoint.c)
          {
            m_cpMarks[p.r][c] = 'A';
            c--;
          }
        }
        else if(p.c < m_sCenterPoint.c)//to the left
        {
          while(c != m_sCenterPoint.c)
          {
            m_cpMarks[p.r][c] = 'A';
            c++;
          }
        }
        else if(p.r < m_sCenterPoint.r)//to the top
        {
          while(r != m_sCenterPoint.r)
          {
            m_cpMarks[r][p.c] = 'A';
            r++;
          }
        }
        else if(p.r > m_sCenterPoint.r)
        {
          while(r != m_sCenterPoint.r)
          {
            m_cpMarks[r][p.c] = 'A';
            r--;
          }
        }
      }
      if(m_nState == 1 && !shipDestroyed)
      {
        m_sCenterPoint.r = p.r;
        m_sCenterPoint.c = p.c;

        //check left and right first (since people like doing H)
        if(p.c+1 < m_nCols && m_cpMarks[p.r][p.c+1] != 'o' && m_cpMarks[p.r][p.c+1] != 'X' && m_cpMarks[p.r][p.c+1] != 'A')
          m_qRight.push(Point(p.r, p.c+1));//push right block
        if(p.c-1 >=0 && m_cpMarks[p.r][p.c-1] != 'o' && m_cpMarks[p.r][p.c-1] != 'X' && m_cpMarks[p.r][p.c-1] != 'A')
          m_qLeft.push(Point(p.r, p.c-1));//push left block
        if(p.r-1 >= 0 && m_cpMarks[p.r-1][p.c] != 'o' && m_cpMarks[p.r-1][p.c] != 'X' && m_cpMarks[p.r-1][p.c] != 'A')
          m_qTop.push(Point(p.r-1, p.c)); //push top block;
        if(p.r+1 < m_nRows && m_cpMarks[p.r+1][p.c] != 'o' && m_cpMarks[p.r+1][p.c] != 'X' && m_cpMarks[p.r+1][p.c] != 'A')
          m_qBot.push(Point(p.r+1, p.c));//push bottom block.

        if(!m_qTop.empty() || !m_qLeft.empty() || !m_qRight.empty() || !m_qBot.empty())
          m_nState = 2;
        else
          m_nState = 1;
      }//end state1
      else if(m_nState == 2 && !shipDestroyed)
      {
        if(p.c > m_sCenterPoint.c && p.r == m_sCenterPoint.r)//if attacked to the right
          {
            if(p.c+1 < m_nCols && m_cpMarks[p.r][p.c+1] != 'o' && m_cpMarks[p.r][p.c+1] != 'X' && m_cpMarks[p.r][p.c+1] != 'A')
              m_qRight.push(Point(p.r, p.c+1));
          }
        if(p.c < m_sCenterPoint.c && p.r == m_sCenterPoint.r)//if attacked to the left
          {
            if(p.c-1 >= 0 && m_cpMarks[p.r][p.c-1] != 'o' && m_cpMarks[p.r][p.c-1] != 'X' && m_cpMarks[p.r][p.c-1] != 'A')
              m_qLeft.push(Point(p.r, p.c-1));
          }
        if(p.r > m_sCenterPoint.r && p.c == m_sCenterPoint.c)//if attacked to the bottom
          {
            if(p.r+1 < m_nRows && m_cpMarks[p.r+1][p.c] != 'o' && m_cpMarks[p.r+1][p.c] != 'X' && m_cpMarks[p.r+1][p.c] != 'A')
              m_qBot.push(Point(p.r+1, p.c));
          }
        if(p.r < m_sCenterPoint.r && p.c == m_sCenterPoint.c)//if attacked to the top
          {
            if(p.r-1 >= 0 && m_cpMarks[p.r-1][p.c] != 'o' && m_cpMarks[p.r-1][p.c] != 'X' && m_cpMarks[p.r-1][p.c] != 'A')
              m_qTop.push(Point(p.r-1, p.c));
          }  

        if(!m_qTop.empty() || !m_qLeft.empty() || !m_qRight.empty() || !m_qBot.empty())
          m_nState = 2;
        else
        {
          m_nState = 1;        
          while(!m_qTop.empty())
            m_qTop.pop();
          while(!m_qLeft.empty())
            m_qLeft.pop();
          while(!m_qRight.empty())
            m_qRight.pop();
          while(!m_qBot.empty())
            m_qBot.pop();
        }
      }//end state2
    }
    else
    {
      //we dont know if ship destroyed or not.
      m_cpMarks[p.r][p.c] = 'o';//empty the respective queues if wrong.
      if(p.c > m_sCenterPoint.c )//&& m_cpMarks[p.r][p.c+1] != 'o' && m_cpMarks[p.r][p.c+1] != 'X')
        {//to the right
          while(!m_qRight.empty())
            m_qRight.pop();
        }
      else if(p.c < m_sCenterPoint.c)// && m_cpMarks[p.r][p.c-1] != 'o' && m_cpMarks[p.r][p.c-1] != 'X')
        {
          while(!m_qLeft.empty())
            m_qLeft.pop();
        }
      else if(p.r > m_sCenterPoint.r )//&& m_cpMarks[p.r+1][p.c] != 'o' && m_cpMarks[p.r+1][p.c] != 'X')
        {
          while(!m_qBot.empty())
            m_qBot.pop();
        }
      else if(p.r < m_sCenterPoint.r )//&& m_cpMarks[p.r-1][p.c] != 'o' && m_cpMarks[p.r-1][p.c] != 'X')
        {
          while(!m_qTop.empty())
            m_qTop.pop();
        }
    }//endShotHit
  }//end validShot
}//End GoodPlayer::RecordAttack()

Point GoodPlayer::recommendAttack()
{
  if(m_nState == 1)
  {
    if(m_nXCounter !=0 && m_nXCounter != m_nTotalX)
    {
      for(int r =0; r< m_nRows; r++)//Find an X and examine its surroundings!
      {
        for(int c =0; c < m_nCols; c++)
        {
          if(m_cpMarks[r][c] == 'X')//check surroundings
          {
            if(c+1 < m_nCols && m_cpMarks[r][c+1] == '.')//right
              return Point(r, c+1);
            else if(c-1 >= 0 && m_cpMarks[r][c-1] == '.')//left
              return Point(r, c-1);
            else if(r+1 < m_nRows && m_cpMarks[r+1][c] == '.')//bot
              return Point(r+1, c);
            else if(r-1 >= 0 && m_cpMarks[r-1][c] == '.')//top
              return Point(r-1, c);
          }
        }
      }
    }//End of X Checker
    do{
        int rand1 = rand() % m_nRows;
        int rand2 = rand() % m_nCols;
        if(m_cpMarks[rand1][rand2] != 'X' && m_cpMarks[rand1][rand2] != 'o' && m_cpMarks[rand1][rand2] != 'A')
          return Point(rand1,rand2);
      }while(true);
  }
  else if(m_nState == 2)
  {
    int nRow = m_lastCellAttacked.r;
    int nCol = m_lastCellAttacked.c;
    if(nRow == m_sCenterPoint.r && nCol == m_sCenterPoint.c)//if hit matches the center point.(just changed to state3)
    {
      if(!m_qRight.empty())
      {
        Point p = m_qRight.top();
        m_qRight.pop();
        return p;
      }
      else if(!m_qLeft.empty())
      {
        Point p = m_qLeft.top();
        m_qLeft.pop();
        return p;
      }
      else if(!m_qTop.empty())
      {
        Point p = m_qTop.top();
        m_qTop.pop();
        return p;
      }
      else if(!m_qBot.empty())
      {
        Point p = m_qBot.top();
        m_qBot.pop();
        return p;
      }
      else
      {
       if(m_nXCounter !=0 && m_nXCounter != m_nTotalX)
       {
        for(int r =0; r< m_nRows; r++)//Find an X and examine its surroundings!
        {
          for(int c =0; c < m_nCols; c++)
          {
            if(m_cpMarks[r][c] == 'X')//check surroundings
            {
              if(c+1 < m_nCols && m_cpMarks[r][c+1] == '.')//right
                return Point(r, c+1);
              else if(c-1 >= 0 && m_cpMarks[r][c-1] == '.')//left
                return Point(r, c-1);
              else if(r+1 < m_nRows && m_cpMarks[r+1][c] == '.')//bot
                return Point(r+1, c);
              else if(r-1 >= 0 && m_cpMarks[r-1][c] == '.')//top
                return Point(r-1, c);
            }
          }
        }
  }
        do{
          int rand1 = rand() % m_nRows;
          int rand2 = rand() % m_nCols;
          if(m_cpMarks[rand1][rand2] != 'X' && m_cpMarks[rand1][rand2] != 'o' && m_cpMarks[rand1][rand2] != 'A')
          return Point(rand1,rand2);
        }while(true);
      }
    }//end initial case.
    else if(nCol > m_sCenterPoint.c)//to the right
    {
      if(m_cpMarks[nRow][nCol] == 'X' && !m_qRight.empty())
      {
        Point p = m_qRight.top();
        m_qRight.pop();
        return p;  
      }
      else if(m_cpMarks[nRow][nCol] == 'o' && !m_qLeft.empty())//then pop left side. what if left side empty
      {
        Point p = m_qLeft.top();
        m_qLeft.pop();
        return p;
      }
      else if(m_cpMarks[nRow][nCol] == 'o' && !m_qTop.empty())
      {
        Point p = m_qTop.top();
        m_qTop.pop();
        return p;
      }
      else if(m_cpMarks[nRow][nCol] == 'o' && !m_qBot.empty())
      {
        Point p = m_qBot.top();
        m_qBot.pop();
        return p;
      }
      else if(!m_qRight.empty())
      {
        Point p = m_qRight.top();
        m_qRight.pop();
        return p;
      }
    }
    else if(nCol < m_sCenterPoint.c)//to the left
    {

      if(m_cpMarks[nRow][nCol] == 'X' && !m_qLeft.empty())
      {
        Point p = m_qLeft.top();
        m_qLeft.pop();
        return p;  
      }
      else if(m_cpMarks[nRow][nCol] == 'o' && !m_qRight.empty())//then pop left side. what if left side empty
      {
        Point p = m_qRight.top();
        m_qRight.pop();
        return p;
      }
      else if(m_cpMarks[nRow][nCol] == 'o' && !m_qTop.empty())
      {
        Point p = m_qTop.top();
        m_qTop.pop();
        return p;
      }
      else if(m_cpMarks[nRow][nCol] == 'o' && !m_qBot.empty())
      {
        Point p = m_qBot.top();
        m_qBot.pop();
        return p;
      }
      else if(!m_qLeft.empty())
      {
        Point p = m_qLeft.top();
        m_qLeft.pop();
        return p;
      }
    }
    else if(nRow < m_sCenterPoint.r)//to the top
    {
      if(m_cpMarks[nRow][nCol] == 'X' && !m_qTop.empty())
      {
        Point p = m_qTop.top();
        m_qTop.pop();
        return p;  
      }
      else if(m_cpMarks[nRow][nCol] == 'o' && !m_qBot.empty())//then pop bot side. what if left side empty
      {
        Point p = m_qBot.top();
        m_qBot.pop();
        return p;
      }
      else if(m_cpMarks[nRow][nCol] == 'o' && !m_qRight.empty())
      {
        Point p = m_qRight.top();
        m_qRight.pop();
        return p;
      }
      else if(m_cpMarks[nRow][nCol] == 'o' && !m_qLeft.empty())
      {
        Point p = m_qLeft.top();
        m_qLeft.pop();
        return p;
      }
      else if(!m_qTop.empty())
      {
        Point p = m_qTop.top();
        m_qTop.pop();
        return p;
      }
    }
    else if(nRow > m_sCenterPoint.r)//to the bottom
    {
      if(m_cpMarks[nRow][nCol] == 'X' && !m_qBot.empty())
      {
        Point p = m_qBot.top();
        m_qBot.pop();
        return p;  
      }
      else if(m_cpMarks[nRow][nCol] == 'o' && !m_qTop.empty())//then pop left side. what if left side empty
      {
        Point p = m_qTop.top();
        m_qTop.pop();
        return p;
      }
      else if(m_cpMarks[nRow][nCol] == 'o' && !m_qRight.empty())
      {
        Point p = m_qRight.top();
        m_qRight.pop();
        return p;
      }
      else if(m_cpMarks[nRow][nCol] == 'o' && !m_qTop.empty())
      {
        Point p = m_qTop.top();
        m_qTop.pop();
        return p;
      }
      else if(!m_qBot.empty())
      {
        Point p = m_qTop.top();
        m_qTop.pop();
        return p;
      }
    }
    //if it gets here, no shot has been returned. so randomize it.
    if(m_nXCounter !=0 && m_nXCounter != m_nTotalX)
    {
      for(int r =0; r< m_nRows; r++)//Find an X and examine its surroundings!
      {
        for(int c =0; c < m_nCols; c++)
        {
          if(m_cpMarks[r][c] == 'X')//check surroundings
          {
            if(c+1 < m_nCols && m_cpMarks[r][c+1] == '.')//right
              return Point(r, c+1);
            else if(c-1 >= 0 && m_cpMarks[r][c-1] == '.')//left
              return Point(r, c-1);
            else if(r+1 < m_nRows && m_cpMarks[r+1][c] == '.')//bot
              return Point(r+1, c);
            else if(r-1 >= 0 && m_cpMarks[r-1][c] == '.')//top
              return Point(r-1, c);
          }
        }
      }
    }
    do{
        int rand1 = rand() % m_nRows;
        int rand2 = rand() % m_nCols;
        if(m_cpMarks[rand1][rand2] != 'X' && m_cpMarks[rand1][rand2] != 'o' && m_cpMarks[rand1][rand2] != 'A')
          return Point(rand1,rand2);
      }while(true);
  }
  return Point(0, 0);
}
/**************END OF CREATING PLAYERS***********************/
//*********************************************************************
//  createPlayer
//*********************************************************************

Player* createPlayer(string type, string nm, const Game& g)
{
    static string types[] = {
        "human", "awful", "mediocre", "good"
    };
    
    int pos;
    for (pos = 0; pos != sizeof(types)/sizeof(types[0])  &&
                                                     type != types[pos]; pos++)
        ;
    switch (pos)
    {
      case 0:  return new HumanPlayer(nm, g);
      case 1:  return new AwfulPlayer(nm, g);
      case 2:  return new MediocrePlayer(nm, g);
      case 3:  return new GoodPlayer(nm, g);
      default: return NULL;
    }
}