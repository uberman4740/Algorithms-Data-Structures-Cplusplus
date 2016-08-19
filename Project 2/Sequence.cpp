//Sequence.cpp

#include "Sequence.h"
#include <cstdlib>
#include <iostream>
using namespace std;

//Default constructor
Sequence::Sequence() : m_nSize(0)
{
	pHead = NULL;
}

void Sequence::dump() const
{
	cout << "Data\t\tPosition" << endl;
	for(Node* pTemp = pHead; pTemp != NULL; pTemp = pTemp->pNext)
		cout << pTemp->m_data << "\t\t" << pTemp->m_nPosition << endl;
	cout << endl;
}
// Destructor - loops to end and deletes previous.
Sequence::~Sequence()
{
	Node* pTemp = pHead;

	for(; pTemp != NULL && pTemp->pNext != NULL; pTemp = pTemp->pNext)
	{
		delete pTemp->pPrev;
		pTemp->pPrev = NULL;
	}

	delete pTemp;
	pTemp = NULL;
	pHead = NULL;
}

//Copy constructor - makes a deep copy.
Sequence::Sequence(const Sequence& cSource)
{
	m_nSize = cSource.m_nSize;

	Node* pFollower = pHead;
	pHead = NULL;
	if(cSource.pHead != NULL){
		for(Node* pTemp = cSource.pHead; pTemp != NULL; pTemp = pTemp->pNext)
		{
			Node* pNew = new Node;
			pNew->m_nPosition = pTemp->m_nPosition;
			pNew->m_data = pTemp->m_data;
			if(pHead == NULL)
			{
				pHead = pNew;
				pNew->pPrev = NULL;
				pNew->pNext = NULL;
				pFollower = pNew;
			}
			else
			{
				pNew->pPrev = pFollower;
				pFollower->pNext = pNew;
				pNew->pNext = NULL;
				pFollower = pNew;
			}
		}
		pFollower->pNext = NULL;
	}
}

//Operator=
//Uses copy constructor and swap function 
//Destructor is called automatically.
Sequence& Sequence::operator=(const Sequence& cSource)
{
	if(this == &cSource)
		return *this;

	Sequence cTemp(cSource);
	swap(cTemp);
	return *this;
}

//Empty Function
//Checks whether the linked list is empty or not.
bool Sequence::empty() const
{
	if(m_nSize == 0)
		return true;
	else
		return false;
}

//Size function
//how many elements are in linked list.
int Sequence::size() const
{
	return m_nSize;
}

//Insert function (two arguments)
/* Inserts into linked list by checking for
whether headnode is initialized, end of list,
and whether there is only one node in the list. */
bool Sequence::insert(int pos, const ItemType& value)
{
	if(pos < 0 || pos > size())
		return false;

	Node* pNew = new Node;

	pNew->m_nPosition = pos;
	pNew->m_data = value;

	if(pHead == NULL)
	{
		pHead = pNew;
		pNew->pPrev = NULL;
		pNew->pNext = NULL;
		m_nSize++;
		return true;
	}	
	else
	{
		Node* pTemp = pHead;
		for(; pTemp != NULL && pTemp->pNext != NULL && pTemp->m_nPosition < pos;)
			pTemp = pTemp->pNext;

		if(pTemp->pPrev == NULL) //inserting at beginning
		{
			if(pTemp->pNext == NULL && pTemp->m_nPosition < pos)
			{
				pTemp->pNext = pNew;
				pNew->pPrev = pTemp;
				pNew->pNext = NULL;
			}
			else
			{
				pNew->m_nPosition =pTemp->m_nPosition;
				pHead = pNew;
				pTemp->pPrev = pNew;
				pNew->pPrev = NULL;
				pNew->pNext = pTemp;
				for(pTemp; pTemp != NULL; pTemp = pTemp->pNext)
					pTemp->m_nPosition++;
			}
			m_nSize++;
			return true;
		}
		else if(pTemp != NULL && pTemp->pNext != NULL)
		{
			pNew->pPrev = pTemp->pPrev;
			pNew->pNext = pTemp;
			pTemp->pPrev->pNext = pNew;
			pTemp->pPrev = pNew;
			for(pTemp; pTemp != NULL; pTemp = pTemp->pNext)
				pTemp->m_nPosition++;
			m_nSize++;
			return true;
		}
		else if(pTemp->pNext == NULL) //Inserting at end of list
		{
			if(pTemp->m_nPosition == pos) // if same position, then insert before.
			{
				pTemp->pPrev->pNext = pNew;
				pNew->pPrev = pTemp->pPrev;
				pTemp->pPrev = pNew;
				pNew->pNext = pTemp;
				while(pTemp != NULL)
				{
					pTemp->m_nPosition++;
					pTemp = pTemp->pNext;
				}
			}
			else
			{
				pTemp->pNext = pNew;
				pNew->pPrev = pTemp;
				pNew->pNext = NULL;
			}
			m_nSize++;
			return true;
		}
	}
	return false; //If all cases fail
}

//Insert Function(One Argument)
/* Given value, finds the best place to put it.
Checks whether headnode is initialized, or if first element,
and last element.*/
bool Sequence::insert(const ItemType& value)
{
	Node* pNew = new Node;

	pNew->m_data = value;

	if(pHead == NULL)
	{
		pNew->m_nPosition = 0;
		pHead = pNew;
		pNew->pPrev = NULL;
		pNew->pNext = NULL;
		m_nSize++;
		return true;
	}
	else
	{
		Node* pTemp = pHead;
		for(; pTemp != NULL && pTemp->pNext !=NULL && pTemp->m_data < value; pTemp = pTemp->pNext);

		if(pTemp->pPrev == NULL)//insert at beginning
		{
			if(value <= pTemp->m_data)
			{
				pNew->m_nPosition = pTemp->m_nPosition;
				pHead = pNew;
				pNew->pNext = pTemp;
				pTemp->pPrev = pNew;
				pNew->pPrev = NULL;
				for(pTemp; pTemp != NULL; pTemp = pTemp->pNext)
					pTemp->m_nPosition++;
			}
			else
			{
				pNew->m_nPosition = pTemp->m_nPosition + 1;
				pTemp->pNext = pNew;
				pNew->pPrev = pTemp;
				pNew->pNext = NULL;
			}
			m_nSize++;
			return true;
		}
		else if(pTemp != NULL && pTemp->pNext != NULL)
		{
			pNew->m_nPosition = pTemp->m_nPosition;
			pNew->pPrev = pTemp->pPrev;
			pTemp->pPrev->pNext = pNew;
			pTemp->pPrev = pNew;
			pNew->pNext = pTemp;
			for(pTemp; pTemp != NULL; pTemp = pTemp->pNext)
				pTemp->m_nPosition++;
			m_nSize++;
			return true;
		}
		else if(pTemp->pNext == NULL)
		{
			if(value < pTemp->m_data)
			{
				pNew->m_nPosition = pTemp->m_nPosition;
				pTemp->m_nPosition++;
				pNew->pNext = pTemp;
				pNew->pPrev = pTemp->pPrev;
				pTemp->pPrev->pNext = pNew;
				pTemp->pPrev = pNew;
			}
			else
			{
				pNew->m_nPosition = pTemp->m_nPosition + 1;
				pNew->pNext = NULL;
				pTemp->pNext = pNew;
				pNew->pPrev = pTemp;
			}
			m_nSize++;
			return true;
		}
	}
	return false; //If all cases fail.
}

//Erase Function
//Calls eraseData given position.
bool Sequence::erase(int pos)
{
	if(pos < 0 || pos > size())
		return false;

	eraseData(pos);	
	return true;
}

//eraseData function
//finds the node and frees the memory.
void Sequence::eraseData(int pos)
{
	Node* pTemp = pHead;
	Node* pTempTwo = NULL;

	for(pTemp; pTemp != NULL && pTemp->m_nPosition != pos; pTemp = pTemp->pNext);
	
		if(pTemp->pPrev == NULL)//head pointer checker
		{
			if(pTemp->pNext == NULL)
				pHead = NULL;
			else
			{
				pHead = pTemp->pNext;
				pTemp->pNext->pPrev = NULL;
			}
		}
		else if(pTemp != NULL && pTemp->pNext != NULL)
		{
			pTemp->pPrev->pNext = pTemp->pNext;
			pTemp->pNext->pPrev = pTemp->pPrev;
		}
		else if(pTemp->pNext == NULL)
			pTemp->pPrev->pNext = NULL;

		pTempTwo = pTemp->pNext;
		while(pTempTwo != NULL)
		{
			pTempTwo->m_nPosition--;
			pTempTwo = pTempTwo->pNext;
		}

	delete pTemp;
	pTemp = NULL;
	m_nSize--;
}

//Remove function
/*Find all positions of the given value
and calls eraseData to do the actual deleting*/
int Sequence::remove(const ItemType& value)
{
	Node* pTemp = pHead;
	int nCounter = 0;
	while(pTemp != NULL)
	{
		if(pTemp->pNext != NULL && pTemp->m_data == value)
		{
			pTemp = pTemp->pNext;
			eraseData(pTemp->pPrev->m_nPosition);
			nCounter++;
		}
		else if(pTemp->pNext == NULL && pTemp->m_data == value)
		{
			eraseData(pTemp->m_nPosition);
			nCounter++;
			return nCounter;
		}
		else if(pTemp->pNext == NULL && pTemp->m_data != value)
		{
			if(nCounter > 0)
				return nCounter;
			else
				return -1;
		}
		else
			pTemp = pTemp->pNext;
	}
	return nCounter;
}
//Get function
/*returns value by reference given the position.
Loops through until position in list matches parameter.*/
bool Sequence::get(int pos, ItemType& value) const
{
	if(pos < 0 || pos >= size())
		return false;

	Node* pTemp = pHead;
	for(pTemp; pTemp != NULL && pTemp->m_nPosition != pos;)
		pTemp = pTemp->pNext;

	value = pTemp->m_data;

	return true;
}
bool Sequence::set(int pos, const ItemType& value)
{
		if(pos < 0 || pos >= size())
			return false;
		Node* pTemp = pHead;

		for(pTemp; pTemp != NULL && pTemp->m_nPosition != pos;)
			pTemp= pTemp->pNext;

		if(pTemp != NULL)
		{
			pTemp->m_data = value;
			return true;
		}
		else
			return false;
}
//Find function
/*Given the value, find the smallest position where
it occurs by looping through the linked list*/
int Sequence::find(const ItemType& value) const
{
	Node* pTemp = pHead;

	for(pTemp; pTemp != NULL && pTemp->m_data != value;)
		pTemp = pTemp->pNext;

	if(pTemp != NULL)
		return pTemp->m_nPosition;
	else
		return -1;
}

//Swap function
//Swap linked lists by changing the pointer of headnode.
void Sequence::swap(Sequence& other)
{
	Node* pTemp = other.pHead;
	other.pHead = pHead;
	pHead = pTemp;

	int nTemp = m_nSize;
	m_nSize = other.m_nSize;
	other.m_nSize = nTemp;
}

//Subsequence
/*Loops until seq2 hits the end of list.
Compares consecutive numbers in seq1 to determine
if subsequence.
Returns -1 if otherwise.*/
int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	if(seq2.empty() || seq1.empty() || (seq1.size() < seq2.size()) )
		return -1;

	ItemType value;
	seq2.get(0, value);
	int nPosition = seq1.find(value); //successfully compares first item in seq2

	if(nPosition != -1) //if found in sequence1
	{
		int jjj = 1;
		for(int iii = nPosition, jjj=1; jjj < seq2.size(); iii++, jjj++)
		{
			ItemType value2;
			seq1.get(iii+1, value);
			seq2.get(jjj, value2);
			if(value != value2)
				nPosition = -1;
		}
	}
	return nPosition;
}

//Interleave function
/*Combines two sequences together by placing one after the other.
Calls copy constructor to a temp Sequence. Insert new data inbetween.
Swap and return. Destructor is called automatically.*/
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	ItemType value;

	Sequence cTemp = seq1;
	int nAdder = 1;
	if(seq2.size() <= seq1.size())
	{
		for(int iii=0; iii < seq2.size(); iii++)
		{
			seq2.get(iii, value);
			cTemp.insert(nAdder, value);
			nAdder+=2;
		}
	}
	else
	{
		for(int iii=0; iii < seq2.size(); iii++)
		{
			seq2.get(iii, value);
			if(nAdder > seq1.size())
			{
				cTemp.insert(nAdder, value);
				nAdder++;
			}
			else
			{
				cTemp.insert(nAdder, value);
				nAdder+=2;
			}
		}
	}
	cTemp.swap(result);
}