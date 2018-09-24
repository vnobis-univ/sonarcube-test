#pragma once
#include <map>
#include "Language.h"

using namespace std;

class TranslationService
{
	Language language;
	map<string, string> table;
public:
	TranslationService();
	TranslationService(Language _language);
	string getWord(string key);
};