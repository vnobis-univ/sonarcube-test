#include "TranslationService.h"
#include <fstream>
#include <string>
#include "Globals.h"

TranslationService::TranslationService() : language(ENG)
{
}

TranslationService::TranslationService(Language _language) : language(_language)
{
	ifstream languageStream;

	switch (language)
	{
	case UKR:
		languageStream.open("Ukr.txt");
		break;
	default:
		languageStream.open("Eng.txt");
		break;
	}

	for (int i = 0; i < amountOfLines; i++)
	{
		string translatedLine;
		getline(languageStream, translatedLine);
		table.insert(pair<string, string>(keys[i], translatedLine));
	}
}

string TranslationService::getWord(string key)
{
	if(table.find(key) == table.end())
	{
		return key;
	}
	return table[key];
}