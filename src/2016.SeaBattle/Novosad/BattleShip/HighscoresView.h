#pragma once
#include "View.h"
#include "TranslationService.h"

class HighscoresView : public View
{
	TranslationService service;
public:
	HighscoresView();
	void draw() override;
	View* handle() override;
};

