#pragma once
#include <string>
#include "View.h"


using std::string;

class LanguageSelection :public View
{
private:
	const string english[2] = { " English "," Ukrainian " };
	const string ukrainian[2] = { " Англійська "," Українська " };
	int selected;

	void printLangOption();

public:

	LanguageSelection(Language m_lang = Language::ENG);

	virtual void draw();
	virtual View* handle();

};