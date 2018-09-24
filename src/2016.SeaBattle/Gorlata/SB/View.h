#pragma once


#include "Utils.h"

enum class Language { ENG, UKR };

class View
{

protected:

	Language lang;


public:
	View::View(Language m_lang = Language::ENG) :
		lang(m_lang)
	{
		showConsoleCursor(false);
	}

	virtual void draw() = 0;
	virtual View* handle() = 0;
};
