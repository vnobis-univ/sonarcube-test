#include "Dictionary.h"


void Dictionary::setCurrentDictionary()
{
	if (currLang == Language::English)
	{
		if (currDifficulty.getDifficulty() == DifficultyModes::Easy)
		{
			in.close();
			in.open("en_Dictionary_easy.txt");
		}
		if (currDifficulty.getDifficulty() == DifficultyModes::Medium)
		{
			in.close();
			in.open("en_Dictionary_medium.txt");
		}
		if (currDifficulty.getDifficulty() == DifficultyModes::Hard)
		{
			in.close();
			in.open("en_Dictionary_hard.txt");
		}
	}
	if (currLang == Language::Ukrainian)
	{
		if (currDifficulty.getDifficulty() == DifficultyModes::Easy)
		{
			in.close();
			in.open("uk_Dictionary_easy.txt");
		}
		if (currDifficulty.getDifficulty() == DifficultyModes::Medium)
		{
			in.close();
			in.open("uk_Dictionary_medium.txt");
		}
		if (currDifficulty.getDifficulty() == DifficultyModes::Hard)
		{
			in.close();
			in.open("uk_Dictionary_hard.txt");
		}
	}
}

Dictionary::Dictionary() :
in("en_Dcitionary_easy")
{
	int i = 0;
	while (in >> arr[i])
	{
		i++;
	}
}
void Dictionary::loadWords()
{
	setCurrentDictionary();
	int i = 0;
	while (in >> arr[i])
	{
		i++;
	}
}

string Dictionary::getWord()
{
	int i = rand() % 20;
	return arr[i];
}