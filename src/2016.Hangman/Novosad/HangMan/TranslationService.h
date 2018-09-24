#pragma once
#include <map>
#include <string>
#include "Language.h"
using namespace std;

class TranslationService
{
private:
	Language language;
	map<string, string> table;
public:
	TranslationService();
	TranslationService(Language _language);
	string getWord(string key);
};

