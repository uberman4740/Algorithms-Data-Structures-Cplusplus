#include <queue>
#include <iostream>
using namespace std;

#ifndef COORD_H
#define COORD_H
class Coord
{
  public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
  private:
    int m_r;
    int m_c;
};
#endif

void checkDirection(queue<Coord>& s,int nRow, int nCol, char maze[][10])
{
  if(maze[nRow][nCol] == '.')
  {
    s.push(Coord(nRow, nCol));
    maze[nRow][nCol] = 'V';
  }
}

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    if(sr < 0 || sc < 0 || er < 0 || ec < 0 || sr > 9 || sc > 9 ||
       er > 9 || ec > 9 || maze[sr][sc] == 'X' || maze[er][ec] == 'X')
      return false;

    queue<Coord> s;
    s.push(Coord(sr, sc)); //calls Coord constructor
    maze[sr][sc] = 'V';

    while(!s.empty())
    {
      Coord cChecker = s.front();
      s.pop();

      int nRow = cChecker.r();
      int nCol = cChecker.c();

	  if(nRow == er && nCol == ec)
		  return true;
	  else
	  {
		  checkDirection(s, nRow-1, nCol, maze);
		  checkDirection(s, nRow, nCol+1, maze);
		  checkDirection(s, nRow+1, nCol, maze);
		  checkDirection(s, nRow, nCol-1, maze);
	  }
    }
	return true;
}