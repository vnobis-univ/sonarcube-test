#include <iostream>
#include <string>
#include "Complexity.h"

using namespace std;

Complexity complexity;

void parseStrToComplexity(const string str)
{
	if (str == "Hard")
	{
		complexity = Complexity::Hard;
	}
	if (str == "Medium")
	{
		complexity = Complexity::Medium;
	}
	if (str == "Easy")
	{
		complexity = Complexity::Easy;
	}
	if (str == "������")
	{
		complexity = Complexity::������;
	}
	if (str == "������i�")
	{
		complexity = Complexity::������i�;
	}
	if (str == "������")
	{
		complexity = Complexity::������;
	}
	if (str == "None")
	{
		complexity = Complexity::None;
	}
}
string parseComplexityToString(Complexity c)
{
	string ret;
	if (c == Complexity::Hard)
	{
		ret = "Hard";
	}
	else if (c == Complexity::Medium)
	{
		ret = "Medium";
	}
	else if (c == Complexity::Easy)
	{
		ret = "Easy";
	}
	else if (c == Complexity::������)
	{
		ret = "������";
	}
	else if (c == Complexity::������i�)
	{
		ret = "������i�";
	}
	else if (c == Complexity::������)
	{
		ret = "������";
	}
	else if (c == Complexity::None)
	{
		ret = "None";
	}
	else
	{
		ret = "ERROR";
	}
	return ret;
}