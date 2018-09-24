#pragma once
#include <conio.h>
#include "View.h"
#include "Lokalization.h"
#include "Buttons.h"
#include "LokalizationView.h"
#include "PreFieldView.h"
#include "HighscoresView.h"

class StartView : public View
{
	string optionEn[4] = { "Start", "Highscore", "Options", "Out" };
	string optionUa[4] = { "Старт", "Досягнення", "Налаштування", "Покинути гру" };
	Lokalization language;
	short position;
public:
	StartView();
	StartView(Lokalization);
	void draw();
	void printMenu();
	View* handle();
};