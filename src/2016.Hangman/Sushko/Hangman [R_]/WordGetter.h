#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "ConsoleUtils.h"

using std::string;
using std::vector;

class WordGetter {
protected:
	Difficulty lvl;
	vector<string> used;

	WordGetter(Difficulty m_lvl);
	bool wasUsed(string word);
public:
	virtual string getWord() = 0;
};

class InetWordGetter : public WordGetter
{
	bool isLetter(char ch);
	string getRandomWord();

public:
	InetWordGetter(Difficulty m_lvl);
	string getWord();
};

class FileWordGetter : public WordGetter
{
	vector<string> words;
public:
	FileWordGetter(Difficulty m_lvl);
	string getWord();
};