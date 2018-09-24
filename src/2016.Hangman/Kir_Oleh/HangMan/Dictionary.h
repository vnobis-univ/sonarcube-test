#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "OptionModes.h"

using namespace::std;


class Dictionary
{
private:
	ifstream in;
	string arr[20];

	void setCurrentDictionary();
public:
	Dictionary();
	void loadWords();
	string getWord();
};

extern Dictionary dict;