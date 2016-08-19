//History.cpp

#include "History.h"
#include <string>
#include <iostream>
#include "globals.h"
using namespace std;

History::History(int nRows, int nCols) : m_row(nRows), m_col(nCols)
{
	int r;
	int c;

	m_grid = new char* [nRows];

	for(r = 0; r < nRows; r++)
		m_grid[r] = new char[nCols];

	for(r = 0; r< nRows; r++)
		for(c = 0; c< nCols; c++)
			m_grid[r][c] = '.';
}

History::~History()
{
	for(int r = 0; r < m_row; r++)
	{
		delete [] m_grid[r];
		m_grid[r] = NULL;
	}

	delete [] m_grid;
	m_grid = NULL;

}

bool History::record(int r, int c)
{
	char cValue;
    if (r <= 0  ||  c <= 0  ||  r > m_row  ||  c > m_col)
		return false;
		
	cValue = m_grid[r-1][c-1];

	if(cValue == 'Z')
		return true;
	else if(cValue == '.')
		m_grid[r-1][c-1] = 'A';
	else if(cValue != 'Z')
		m_grid[r-1][c-1] = cValue + 1;
	return true;
}

void History::display() const
{
	clearScreen();
	for(int r=1; r <= m_row; r++)
	{
		for(int c=1; c <= m_col; c++)
			cout << m_grid[r-1][c-1];
		cout << endl;
	}
}