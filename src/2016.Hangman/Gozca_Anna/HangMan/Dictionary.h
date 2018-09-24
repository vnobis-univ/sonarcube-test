#pragma once
#include <iostream>
#include <string>
#include "Printers.h"
#include "ConsoleUtils.h"
#include "GlobalVar.h"
#include <fstream>
using namespace std;

class Dictionary
{
private:
	static const size_t numberOfWords = 20;
	string words[numberOfWords];
public:
	Dictionary();
	Dictionary(Levels lev);	
	void readWordsForLevel(Levels lev);
	string getWord(int i);
};
