#pragma once
#include <string>

enum class Complexity
{
	Hard,
	Medium,
	Easy,
	������,
	������i�,
	������,
	None,
};

extern Complexity complexity;
void parseStrToComplexity(std::string str);
std::string parseComplexityToString(Complexity c);
