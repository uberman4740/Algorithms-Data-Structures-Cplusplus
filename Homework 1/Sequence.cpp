//Sequence.cpp

#include "Sequence.h"
#include <iostream>
using namespace std;

Sequence::Sequence() : m_nSize(0) {}

void Sequence::dump()
	{
		for(int iii = 0; iii < size(); iii++)
		{
			cout << m_data[iii];
			cout << endl;
		}
	}

bool Sequence::empty() const
	{
		if(m_nSize == 0)
			return true;
		else
			return false;
	}

int Sequence::size() const
	{
		return m_nSize;
	}

bool Sequence::insert(int pos, const ItemType& value)
	{
		if(pos < 0 || pos > size() || size() == DEFAULT_MAX_ITEMS)
			return false;
		else
			insertData(pos, value);
		return true;
	}

bool Sequence::insert(const ItemType& value)
	{
		if(size() == DEFAULT_MAX_ITEMS)
			return false;

		int iii=0;
		for(iii; iii< size(); iii++)
		{
			if(value <= m_data[iii])
			{
				insertData(iii, value);
				return true;
			}
		}
		m_data[iii] = value;
		m_nSize++;
		return true;
	}

void Sequence::insertData(int pos, const ItemType& value)
	{
		for(int iii = size(); iii > pos; iii--)
			m_data[iii] = m_data[iii - 1];
		m_data[pos] = value;
		m_nSize++;
	}

bool Sequence::erase(int pos)
	{
		if(pos < 0 || pos >= size())
			return false;

		eraseData(pos);
		// for(int iii= pos; iii < size()-1; iii++)
		// 	m_data[iii] = m_data[iii+1];

		return true;
	}

void Sequence::eraseData(int pos)
	{
		for(int iii= pos; iii < size(); iii++)
			m_data[iii] = m_data[iii+1];

		m_nSize--;		
	}


int Sequence::remove(const ItemType& value)
	{
		int nCounter = 0;
		for(int iii=size() -1 ; iii >= 0; iii--)
		{
			if(m_data[iii] == value)
			{
				eraseData(iii);
				nCounter++;
			}
		}
		return nCounter;
	}

bool Sequence::get(int pos, ItemType& value) const
	{
		if(pos <0 || pos >= size())
			return false;

		value = m_data[pos];
		return true;
	}

bool Sequence::set(int pos, const ItemType& value)
	{
		if(pos < 0 || pos >= size())
			return false;

		m_data[pos] = value;
		return true;
	}

int Sequence::find(const ItemType& value) const
	{
		for(int iii = 0; iii < size(); iii++)
		{
			if(m_data[iii] == value)
				return iii;
		}
		return -1;
	}

void Sequence::swap(Sequence& other)
	{
		int nTemp = other.m_nSize;
		other.m_nSize = m_nSize;
		m_nSize = nTemp;

		int nMaxSize;

		if(other.size() >= size())
			nMaxSize = other.size();
		else
			nMaxSize = size();

		for(int iii=0; iii< nMaxSize; iii++)
		{
			ItemType temp = m_data[iii];
			m_data[iii] = other.m_data[iii];
			other.m_data[iii] = temp;
		}
	}