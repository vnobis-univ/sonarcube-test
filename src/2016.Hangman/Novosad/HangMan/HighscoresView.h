#pragma once
#include "View.h"
#include "TranslationService.h"
class HighscoresView :
	public View
{
private:
	TranslationService service;
public:
	HighscoresView();
	void draw();
	View* handle();
};

