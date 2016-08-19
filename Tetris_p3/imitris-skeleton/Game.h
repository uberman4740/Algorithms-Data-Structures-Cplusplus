#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Tank.h"
#include "UserInterface.h"
#include <string>
// [Add other #include directives as necessary.]

class Game
{
  public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
    // [Add other members as necessary.]

  private:
    Tank    m_tank;
    Screen  m_screen;
    int     m_level;
    // [Add other members as necessary.]
};

#endif // GAME_INCLUDED
