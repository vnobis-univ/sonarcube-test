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
	if (str == "Тяжкий")
	{
		complexity = Complexity::Тяжкий;
	}
	if (str == "Середнiй")
	{
		complexity = Complexity::Середнiй;
	}
	if (str == "Легкий")
	{
		complexity = Complexity::Легкий;
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
	else if (c == Complexity::Тяжкий)
	{
		ret = "Тяжкий";
	}
	else if (c == Complexity::Середнiй)
	{
		ret = "Середнiй";
	}
	else if (c == Complexity::Легкий)
	{
		ret = "Легкий";
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