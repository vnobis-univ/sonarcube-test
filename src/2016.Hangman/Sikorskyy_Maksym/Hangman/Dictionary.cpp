#include "Dictionary.h"


void Dictionary::setCurDictionary()
{
	if (currLang == Language::English)
	{
		if (currMode == DifficultyModes::Easy)
		{
			in.close();
			in.open("E1.txt");
		}
		if (currMode == DifficultyModes::Medium)
		{
			in.close();
			in.open("E2.txt");
		}
		if (currMode == DifficultyModes::Hard)
		{
			in.close();
			in.open("E3.txt");
		}
	}
	if (currLang == Language::Ukrainian)
	{
		if (currMode == DifficultyModes::Easy)
		{
			in.close();
			in.open("U1.txt");
		}
		if (currMode == DifficultyModes::Medium)
		{
			in.close();
			in.open("U2.txt");
		}
		if (currMode == DifficultyModes::Hard)
		{
			in.close();
			in.open("U3");
		}
	}
}

Dictionary::Dictionary() :
in("E1")
{
	int i = 0;
	while (in >> arr[i])
	{
		i++;
	}
}
void Dictionary::loadWords()
{
	setCurDictionary();
	int i = 0;
	while (in >> arr[i])
	{
		i++;
	}
}

void Dictionary::printWords()
{
	for (int i = 0; i < 20; ++i)
	{
		cout << arr[i] << endl;
	}
}

string Dictionary::getWord()
{
	int i = rand() % 20;
	return arr[i];
}