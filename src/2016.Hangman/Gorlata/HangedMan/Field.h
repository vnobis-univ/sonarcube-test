#pragma once
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "View.h"
#include "Levels.h"
#include "Dictionary.h"
#include "Alphabet.h"


using std::string;


class Field: public View
{
	LevelState difficulty;
	int scores;
	int health;
	Dictionary dictionary;
	Alphabet alphabet;

	void guessLetter(char let, string& word, string& progress);
	bool guessWord(string& word, string& progress);

public:

	Field(LevelState chosen_difficulty, Language m_lang);


	void draw();
	View* handle();

};




