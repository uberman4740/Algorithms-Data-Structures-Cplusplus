#include <stack>
#include <iostream>
#include <string>
using namespace std;

bool precedenceChecker(stack<char>& sHold, const char oper, string& postfix)
{
	if(oper == '|')
	{
		postfix += sHold.top();
		sHold.pop();
	}
	else if(oper == '&' && (sHold.top() == '&' || sHold.top() == '!'))
	{
		postfix += sHold.top();
		sHold.pop();
	}
	else if(oper == '!' && sHold.top() == '!')
	{
		postfix += sHold.top();
		sHold.pop();
	 }
	 else
	 	return false;

	 return true;
}

char postfixReader(const string& postfix)
{
	stack<char> spfReader;
	char cOperand1;
	char cOperand2;
	char cFinal;
	for(size_t iii=0; iii < postfix.length(); iii++)
	{
		if(postfix[iii] == 'T' || postfix[iii] == 'F')
			cFinal = postfix[iii];
		else if(postfix[iii] == '|')
		{
			cOperand2 = spfReader.top();
			spfReader.pop();
			if(!spfReader.empty())
				{
					cOperand1 = spfReader.top();
					spfReader.pop();
				}
			if(cOperand1 == cOperand2)
				cFinal = cOperand1;
			else
				cFinal = 'T';
		}
		else if(postfix[iii] == '&')
		{
			cOperand2 = spfReader.top();
			spfReader.pop();
			if(!spfReader.empty())
				{
					cOperand1 = spfReader.top();
					spfReader.pop();
				}

			if(cOperand1 == cOperand2)
				cFinal = cOperand1;
			else
				cFinal = 'F';
		}
		else if(postfix[iii] == '!')
		{
			cOperand1 = spfReader.top();
			spfReader.pop();
			if(cOperand1 == 'T')
				cFinal = 'F';
			else
				cFinal = 'T';
		}
		spfReader.push(cFinal);
	}
	//if(spfReader.empty()
	return spfReader.top();
}

int evaluate(const string& infix, string& postfix, bool& result)
{
	postfix = ""; // set to empty string
	string nospaces = "";

	//convert infix to a string with no spaces.
	for(size_t iii = 0; iii < infix.length(); iii++)
	{
		if(infix[iii] != ' ')
			nospaces += infix[iii];
	}

	stack<char> sHold;
	int nFrPrent = 0;
	int nBkPrent = 0;
	
	for(size_t iii = 0; iii < nospaces.length(); iii++)
	{
		switch(nospaces[iii])
		{
			case 'T':
				if(iii+1 < nospaces.length())
				{
					char chck = nospaces[iii+1];
					if(chck == 'T' || chck == 'F' || chck == '(' || chck =='!')
						return 1;
				}
				postfix += nospaces[iii];
				break;
			case 'F':
				if(iii+1 < nospaces.length())
				{
					char chck = nospaces[iii+1];
					if(chck == 'T' || chck == 'F' || chck == '(' || chck =='!')
						return 1;
				}
				postfix += nospaces[iii];
				break;
			case '(':
				if(iii+1 == nospaces.length())
					return 1;

				if(iii+1 < nospaces.length())
				{
					char chck = nospaces[iii+1];
					if(chck == '|' || chck == '&')
						return 1;
				}
				sHold.push(nospaces[iii]);
				nFrPrent++;
				break;
			case ')':
				if(iii+1 < nospaces.length())
				{
					char chck = nospaces[iii+1];
					if(chck == '(' || chck == 'T' || chck == 'F')
						return 1;
				}
				while(!sHold.empty() && sHold.top() != '(')
				{
					postfix += sHold.top();
					sHold.pop();
				}
				if(sHold.size() == 1 && sHold.top() != '(')
					return 1;
				sHold.pop(); //remove the '('
				nBkPrent++;
				break;
			case '!':
				if(iii+1 < nospaces.length())
				{
					char chck = nospaces[iii+1];
					if(chck == '&' && chck == '|' && chck == ')')
						return 1;
				}
				if(iii+1 == nospaces.length())
					return 1;
				while(!sHold.empty() && sHold.top() != '(' && 
					precedenceChecker(sHold, nospaces[iii], postfix));
				sHold.push(nospaces[iii]);
				break;
			case '&':
				if(iii+1 == nospaces.length())
					return 1;

				if(iii+1 < nospaces.length())
				{
					char chck = nospaces[iii+1];
					if(chck == '&' || chck == '|' || chck == ')')
						return 1;
				}
				while(!sHold.empty() && sHold.top() != '(' && 
					precedenceChecker(sHold, nospaces[iii], postfix));
				sHold.push(nospaces[iii]);
				break;
			case '|':
				if(iii+1 == nospaces.length())
					return 1;

				if(iii+1 < nospaces.length())
				{
					char chck = nospaces[iii+1];
					if(chck == '&' || chck == '|' || chck == ')')
						return 1;
				}
				while(!sHold.empty() && sHold.top() != '(' && 
					precedenceChecker(sHold, nospaces[iii], postfix));
				sHold.push(nospaces[iii]);
				break;
		}
	}
	while(!sHold.empty())
	{
		postfix += sHold.top();
		sHold.pop();
	}

	if(nFrPrent != nBkPrent || postfix.empty())
		return 1;

	char cCheck = postfixReader(postfix);
	if(cCheck != 'T' && cCheck != 'F')
		return 1;
	else if(cCheck == 'T')
		result = true;
	else
		result = false;

	return 0;
}