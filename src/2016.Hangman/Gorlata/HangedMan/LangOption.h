#pragma once
#include "View.h"
#include <string>

using std::string;

class LangOption:public View
{
private:
	const string english[2] = {" English "," Ukrainian "};
	const string ukrainian[2] = { " Англійська "," Українська " };
	int selected;

	void printLangOption();

public:
	
	LangOption(Language m_lang = Language::ENG);

	virtual void draw();
	virtual View* handle();

};

