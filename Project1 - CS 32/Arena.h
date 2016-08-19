//Arena.h

#ifndef ARENA_H
#define ARENA_H

#include <string>
#include "globals.h"
#include "History.h"
class Robot;
class Player;

class Arena
{
  public:
      // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

      // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     robotCount() const;
    int     getCellStatus(int r, int c) const;
    int     numberOfRobotsAt(int r, int c) const;
    void    display(std::string msg) const;
	History& history();
      // Mutators
    void   setCellStatus(int r, int c, int status);
    bool   addRobot(int r, int c, int channel);
    bool   addPlayer(int r, int c);
    std::string moveRobots(int channel, int dir);

  private:
    int     m_grid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Robot*  m_robots[MAXROBOTS];
	History m_history;
    int     m_nRobots;

      // Helper functions
    void checkPos(int r, int c) const;
    bool isPosInBounds(int r, int c) const;
	
};

#endif