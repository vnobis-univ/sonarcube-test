#pragma once
#include <conio.h>
#include "View.h"
#include "Lokalization.h"
#include "Buttons.h"
#include "StartView.h"

class LokalizationView : public View
{
	string optionsEn[2] = { "English", "Ukrainian" };
	string optionsUa[2] = { "Англійська", "Українська" };
	Lokalization language;
	int position;
public:
	LokalizationView();
	LokalizationView(Lokalization);
	void draw();
	void printMenu();
	View* handle();
};