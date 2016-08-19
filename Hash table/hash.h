#include <list>
using namespace std;

#ifndef HASHTABLE_H
#define HASHTABLE_H

class Entry
{
	public:
		int m_nOffset;
		string m_sData;
		Entry(const string& s, int offset) : m_nOffset(offset), m_sData(s) {}
};

class HashTable
{
	public:
		HashTable(int size);
		void insert(string sData, int nOffset);
		int find(string sData);
		int encrypt(string sData);
		~HashTable() {}
		list<Entry>* getTable() { return table; }
	private:
		int m_nSize;
		list<Entry>* table;
};

#endif