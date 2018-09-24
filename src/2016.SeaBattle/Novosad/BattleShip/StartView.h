#pragma once
#include "View.h"
#include "Options.h"
#include "TranslationService.h"

using namespace std;

class StartView : public View
{
	TranslationService service;
	int selectedOption = 0;
	Options availableOptions[4];
	string convertToString(Options option);
	View* applyOption();
public:
	StartView();
	void draw() override;
	View* handle() override;
};
