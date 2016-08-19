//testSequence.cpp

#include <cassert>
#include <iostream>
#include "Sequence.h"
using namespace std;

int main()
{
	Sequence s1;
	Sequence s2;

	ItemType value = 6;
	int nCounter = 0;

	s1 = s2;
	s1.swap(s2);
	assert(s1.empty() == true && s2.empty() == true);
	//insert 5 values into s1. ---testing both insert and size and find
	s1.insert(0);
	s1.insert(1);
	s1.insert(2);
	s1.insert(35);
	nCounter += 4;
	assert(s1.empty() == false && s2.empty() == true);
	//insert into position 0 of s1.
	s1.insert(0, value);
	nCounter++;
	assert(s1.size() == nCounter);
	assert(s1.find(value) == 0); //should be at index 0 since used insert.
	assert(s1.find(35) == 4);
	assert(s1.find(-1000) == -1); // should return -1 if not found.

	//insert into invalid positions of s1;
	assert(s1.insert(-5, value) == false);
	assert(s1.insert(nCounter+1, value) == false);

	//testing swap
	s1.swap(s2);
	assert(s2.size() == nCounter);
	assert(s2.find(value) == 0); //should be at index 0 since used insert.
	assert(s2.find(35) == 4);

	//testing erase and remove
	//insert duplicates
	Sequence s3;
	assert(s3.size() == 0);

	for(int iii=0; iii < 20; iii++)
		s3.insert(0, value);

	assert(s3.size() == 20);
	assert(s3.find(value) == 0); //should return the lowest index.

	assert(s3.remove(value) == 20); //should remove all 20 values;
	assert(s3.size() == 0);
	assert(s3.remove(value) == 0);

	s3.insert(0);
	s3.insert(15);
	s3.insert(20);
	s3.insert(25);
	assert(s3.find(0) == 0);
	s3.erase(0);
	assert(s3.find(0) == -1);
	assert(s3.find(15) == 0);
	assert(s3.find(25) == 2); //indexes should have dropped one each.

	//test get and set
	s3.get(0, value);
	assert(value == 15);

	s3.set(0, value+1);
	assert(s3.find(16) == 0); // 16 should be at index 0 now.
	cout << "passed all tests" << endl;
}