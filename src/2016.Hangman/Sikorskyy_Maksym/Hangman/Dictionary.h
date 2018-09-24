#pragma once
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "SavingWinners.h"

using namespace::std;

enum class Language{ Ukrainian, English };
extern Language currLang;

class Dictionary
{
private:
	ifstream in;
	string arr[20];

	void setCurDictionary();
public:
	Dictionary();
	void loadWords();
	void printWords();
	string getWord();
};

extern Dictionary dict;