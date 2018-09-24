#include "Dictionary.h"
#include "Globals.h"
#include <fstream>

Dictionary::Dictionary(){}

string Dictionary:: getWord(int i)
{
	return words[i];
}

void Dictionary:: readWordsFromFile(LevelOptions level)
{
	ifstream file;
	switch (level)
	{
	case LevelOptions::Easy:
	{
		if (language == Language::ENG)
		{
			file = ifstream("Easy.txt");
		}
		else
		{
			file = ifstream("EasyUkr.txt");
		}
		break;
	}
	case LevelOptions::Middle:
	{
		if (language == Language::ENG)
		{
			file = ifstream("Middle.txt");
		}
		else
		{
			file = ifstream("MiddleUkr.txt");
		}
		break;
	}
	case LevelOptions::Hard:
	{
		if (language == Language::ENG)
		{
			file = ifstream("Hard.txt");
		}
		else
		{
			file = ifstream("HardUkr.txt");
		}
		break;
	}
	}
	for (int i = 0; i < amountOfWords; i++)
	{
		file >> words[i];
	}
}

Dictionary::Dictionary(LevelOptions level)
{
	readWordsFromFile(level);
}

