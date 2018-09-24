#pragma once
#include <string>

enum class Language
{
	ENGLISH,
	UKRAINIAN
};

extern Language language;

void setLangToEng();
void setLangToUkr();

void setOptionForStartMenu(std::string* &options);
void setOptionForOptionMenu(std::string* &options);
void setOptionForGameMenu(std::string* &options);