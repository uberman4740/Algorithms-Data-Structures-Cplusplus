#include "hash.h"
#include <string>
#include <list>
#include <iostream>
using namespace std;

HashTable::HashTable(int size) : m_nSize(size)
{
	table = new list<Entry>[size];
}

HashTable::~HashTable()
{
	delete [] table;
}

int HashTable::encrypt(string sData)
{
	unsigned long hash = 5381;
	for(int i = 0; i < sData.size(); i++)
		hash = (hash << 5) + hash + sData[i];
	return hash % m_nSize;
}

void HashTable::insert(string sData, int nOffset)
{
	int nIndex = encrypt(sData);
	table[nIndex].push_back(Entry(sData, nOffset));
}

int HashTable::find(string sData)
{
	int nIndex = encrypt(sData);
	for(list<Entry>::iterator it = table[nIndex].begin(); it != table[nIndex].end(); it++)
	{
		if(sData == it->m_sData)
		{
			//store offset
			int nOffset = it->m_nOffset;
			//delete iterator.
			table[nIndex].erase(it);
			//return the offset.
			return nOffset;
		}
	}
	return -1; //if it breaks out of loop. return -1.
}