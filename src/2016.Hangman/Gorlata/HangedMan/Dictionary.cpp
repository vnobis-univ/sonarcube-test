#include "Dictionary.h"
#include <fstream>


using namespace std;

Word::Word(string my_word, bool m_used) :
	word(my_word),
	used(m_used)
	{};



Dictionary::Dictionary(LevelState chosen, Language m_lang = Language::ENG) :
	listOfWords(vector<Word>(0))
{
	fstream file;
	if (m_lang == Language::ENG)
	{
		switch (chosen)
		{
		case LevelState::EASY:
			file = fstream("DictionaryEASY.txt");
			break;

		case LevelState::MEDIUM:
			file = fstream("DictionaryMED.txt");
			break;

		case LevelState::HARD:
			file = fstream("DictionaryHARD.txt");
			break;
		}
	}
	else
	{
		switch (chosen)
		{
		case LevelState::EASY:
			file = fstream("UkrEASY.txt");
			break;

		case LevelState::MEDIUM:
			file = fstream("UkrMED.txt");
			break;

		case LevelState::HARD:
			file = fstream("UkrHARD.txt");
			break;
		}
	}
	
	string temp;

	while (file >> temp)
	{
		listOfWords.push_back(temp);
	}


}
string Dictionary::getWord()
{
	int index = rand() % listOfWords.size();
	
	while (listOfWords[index].used)
	{
		index = rand() % listOfWords.size();
	}

	listOfWords[index].used = true;

	return listOfWords[index].word;
}
;
