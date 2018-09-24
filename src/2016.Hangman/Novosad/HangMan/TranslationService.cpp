#include "TranslationService.h"
#include <fstream>
#include <string>
#include "Globals.h"

TranslationService::TranslationService()
{
}

TranslationService::TranslationService(Language _language)
{
	ifstream ukr("Ukr.txt");
	ifstream eng("Eng.txt");
	for (int i = 0; i < amountOfLines; i++)
	{
		string translatedLine;
		if (_language == Language::UKR)
		{
			getline(ukr, translatedLine);
		}
		else
		{
			getline(eng, translatedLine);
		}
	table.insert(pair<string, string>(lines[i], translatedLine));
	}
}

string TranslationService::getWord(string key)
{
	return  table.find(key)->second;
}
