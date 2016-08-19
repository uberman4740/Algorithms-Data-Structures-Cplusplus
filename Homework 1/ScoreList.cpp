//ScoreList.cpp

#include "ScoreList.h"

ScoreList::ScoreList(){}

bool ScoreList::add(unsigned long score)
	{
		if(score < 0 || score > 100 || (m_cSeq.size() == 100))
			return false;

		m_cSeq.insert(score);
		return true;
	}

bool ScoreList::remove(unsigned long score)
	{
		int nChecker;
		
		nChecker = m_cSeq.find(score);

		bool removed = m_cSeq.erase(nChecker);
		return (removed);
	}

int ScoreList::size() const
	{
		return m_cSeq.size();
	}

unsigned long ScoreList::minimum() const
	{
		if(m_cSeq.empty())
			return NO_SCORE;

		unsigned long nMin = 100;
		unsigned long nChecker;
		for(int iii=0; iii < size(); iii++)
		{
			m_cSeq.get(iii, nChecker);
			if(nChecker < nMin)
				nMin = nChecker;
		}
		return nMin;
	}

unsigned long ScoreList::maximum() const
	{
		if(m_cSeq.empty())
			return NO_SCORE;

		unsigned long nMax = 0;
		unsigned long nChecker;
		for(int iii=0; iii < size(); iii++)
		{
			m_cSeq.get(iii, nChecker);
			if(nChecker > nMax )
				nMax = nChecker;
		}
		return nMax;
	}

