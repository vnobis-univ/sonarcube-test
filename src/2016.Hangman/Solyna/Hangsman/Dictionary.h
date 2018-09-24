#pragma once
#include <fstream>
#include "View.h"

class Dictionary
{
	static const int sizeOfArray = 40;
	string arrayOfWords[sizeOfArray];
	string arrayOfUsed[sizeOfArray];
	int counter;
public:
	Dictionary(Difficulty d, Languages l);
	string getRandomWord();
	
};

