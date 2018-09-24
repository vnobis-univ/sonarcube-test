#pragma once
#include "Letter.h"
#include <string>
using namespace std;
class Word
{
private:
	int length;
	Letter* letters;
public:
	Word();
	int getLength();
	Letter* getLetters();
	Word(string str);
	friend ostream& operator<< (ostream& out, Word& word);
};


