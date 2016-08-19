//testScoreList.cpp

#include "ScoreList.h"
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
	ScoreList s;
	int nCounter = 0;

	//Test add function
	for(int iii=0; iii< 50; iii++)
	{
		s.add(iii);
		nCounter++;
	}

	for(int iii=0; iii< 10; iii++)
	{
		s.add(0);
		nCounter++;
	}

	s.add(-1);
	s.add(101);
	assert(s.remove(-1) == false && s.remove(101) == false);
	assert(s.size() == nCounter);
	assert(s.maximum() == 49);
	assert(s.minimum() == 0);

	//Check remove function
	assert(s.remove(0) == true);
	nCounter--;
	assert(s.minimum() == 0);
	assert(s.remove(100) == false);
	assert(s.remove(49) == true);
	nCounter--;
	assert(s.maximum() == 48);
	assert(s.size() == nCounter);

	//Make sure it removes only one of duplicates.
	s.add(0);
	nCounter++;
	assert(s.size() == nCounter);

	//Check for NO_SCORE
	ScoreList s2;
	assert(s2.size() == 0);
	assert(s2.maximum() == NO_SCORE);
	assert(s2.minimum() == NO_SCORE);

	cout << "Passed all tests." << endl;
}