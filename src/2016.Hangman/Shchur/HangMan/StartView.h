#pragma once
#include "View.h"
#include <conio.h>
#include "Lokalization.h"
#include "OptionView.h"
#include <Windows.h>

using namespace std;

class StartView : public View
{
	string optionUa[4] = { "Старт", "Таблиця рекордів", "Настройки", "Вихід" };
	string optionEn[4] = { "Start", "Highscore", "Options", "Out" };
	Lokalization language;
	Complexity complexity;
	short position;
public:
	StartView();
	StartView(Lokalization, Complexity);
	void draw();
	void printMenu();
	//void drawMan();
	void drawCopyright();
	View* handle();
};