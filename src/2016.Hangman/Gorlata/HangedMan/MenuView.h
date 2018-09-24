#pragma once

#include <string>
#include "View.h"

using std::string;


class MenuView : public View
{
	const string option[4] = { " Start ", " High Score ", " Language "," Exit " };
	const string ukr_option[4] = { " Почати ", " Таблиця результатів ", " Мова гри ", " Вихід " };
	int selected;

	void printMenu();
public:

	MenuView(Language m_lang = Language::ENG);

	virtual void draw();
	virtual View* handle();
};
