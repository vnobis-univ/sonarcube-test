#pragma once
#include "View.h"
#include <string>
#include <conio.h>
#include "LevelOptions.h"
#include "TranslationService.h"
using namespace std;

class LevelView :
	public View
{
private:
	TranslationService service;
	int selectedOption = 0;
	LevelOptions options[3];
	View* applyOption();
public:
	LevelView();
	void draw();
	View* handle();

};

