#pragma once


#include <string>
#include "View.h"

using std::string;


class MenuView : public View
{
	const string option[3] = { " Start ", " Changing Of The Language "," Exit " };
	const string ukr_option[3] = { " Старт ", " Зміна Мови ", " Вийти " };
	int selected;

	void printMenu();
public:

	MenuView(Language m_lang = Language::ENG);

	virtual void draw();
	virtual View* handle();
};


