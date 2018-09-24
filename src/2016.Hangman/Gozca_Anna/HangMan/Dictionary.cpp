#include "Dictionary.h"

Dictionary::Dictionary() {}

Dictionary::Dictionary(Levels lev) 
{
	if (lev == Levels::EASY)
	{
		ifstream easy("Dictionary(Easy_Eng).txt");
		for (size_t i = 0; i < numberOfWords; i++)
		{
			easy >> words[i];
		}
	}
	if (lev == Levels::MEDIUM)
	{
		ifstream medium("Dictionary(Medium_Eng).txt");
		for (size_t i = 0; i < numberOfWords; i++)
		{
			medium >> words[i];
		}
	}
	if (lev == Levels::HARD)
	{
		ifstream hard("Dictionary(Hard_Eng).txt");
		for (size_t i = 0; i < numberOfWords; i++)
		{
			hard >> words[i];
		}
	}
}

void Dictionary::readWordsForLevel(Levels lev)
{
	if (lev == Levels::EASY)
	{
		ifstream easy("Dictionary(Easy_Eng).txt");
		for (size_t i = 0; i < numberOfWords; i++)
		{
			easy >> words[i];
		}
	}
	if (lev == Levels::MEDIUM)
	{
		ifstream medium("Dictionary(Medium_Eng).txt");
		for (size_t i = 0; i < numberOfWords; i++)
		{
			medium >> words[i];
		}
	}
	if (lev == Levels::HARD)
	{
		ifstream hard("Dictionary(Hard_Eng).txt");
		for (size_t i = 0; i < numberOfWords; i++)
		{
			hard >> words[i];
		}
	}
}

string Dictionary::getWord(int i)
{
	return words[i];
}
