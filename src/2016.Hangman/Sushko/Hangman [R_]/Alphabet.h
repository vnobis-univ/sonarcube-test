#pragma once
#include "ConsoleUtils.h"
#include <iostream>
#include <vector>

using std::vector; 

class Alphabet
{
	struct Char
	{
		char ch;
		bool wasUsed;

		Char(char l, bool = false);
	};
	vector<Char> vec;
public:
	Alphabet() {};
	Alphabet(Lang);

	void reset();

	void setUsed(char c);
	bool validateKeypress(int key);

	friend std::ostream& operator<<(std::ostream& os, const Alphabet& obj);
};
