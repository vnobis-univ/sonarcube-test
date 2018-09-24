#pragma once
#include <string>
#include "LevelOptions.h"
using namespace std;

class Dictionary
{
private:
	const static int amountOfWords = 20;
	string words[amountOfWords];
	void readWordsFromFile(LevelOptions level);
public:
	Dictionary();
	string getWord(int i);
	Dictionary(LevelOptions level);
};

