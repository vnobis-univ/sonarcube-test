#pragma once
#include <vector>
#include <string>
#include "Levels.h"
#include "View.h"

using std::vector;
using std::string;

struct Word
{
	string word;
	bool used;

	
	Word(string my_word = " - ", bool m_used = false);
};


class Dictionary
{
	vector<Word> listOfWords;
	

public:
	
	Dictionary( LevelState chosen, Language m_lang);
	string  getWord();



};
