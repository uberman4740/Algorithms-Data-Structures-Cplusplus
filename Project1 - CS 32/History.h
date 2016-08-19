//History.h

#ifndef HISTORY_H
#define HISTORY_H

class Arena;

class History
{
	public:
		History(int nRows, int nCols);
		~History();
		bool record(int r, int c);
		void display() const;
	private:
		int m_row;
		int m_col;
		char** m_grid;
};

#endif