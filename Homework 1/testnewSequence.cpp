//testnewSequence.cpp

#include "newSequence.h"
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
	Sequence s0(40);
	Sequence s1(50);
	int nCounter = 0;

	assert(s0.empty() == true);
	assert(s1.empty() == true);

	for(int iii=0; iii< 40; iii++) // fill up s0.
		s0.insert(iii);

	assert(s0.find(0) == 0);

	assert(s0.size() == 40);
	assert(s0.insert(0, 2) == false);
	assert(s0.size() == 40); //its filled.
	assert(s0.find(0) == 0); //since it's filled, should not input.

	s1.swap(s0);
	assert(s1.size() == 40);
	s1.swap(s0);
	assert(s1.size() == 0);

	Sequence s2 = s0;
	assert(s2.size() == 40); // Test copy constructor
	assert(s2.find(0) == 0);
	Sequence s3;
	s3 = s0; // Test operator=
	assert(s3.size() == 40);
	assert(s3.find(0) == 0);

	s3 = s3;
	assert(s3.size() == 40);
	s3.remove(0);
	assert(s3.size() == 39);
	assert(s0.size() == 40);
	assert(s0.find(0) == 0);
	s0.erase(0);
	assert(s0.find(1) == 0);

	cout << "Passed all tests." << endl;
}