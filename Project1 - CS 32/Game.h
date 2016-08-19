//Game.h

#ifndef GAME_H
#define GAME_H

#include <string>
class Arena;

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    std::string takePlayerTurn();
    std::string takeRobotsTurn();
};

bool recommendMove(const Arena& a, int r, int c, int& bestDir); //Used only by Game class
int computeDanger(const Arena& a, int r, int c);			    //Used only by Game class
bool charToDir(char ch, int& dir);								//Used only by Game class

#endif