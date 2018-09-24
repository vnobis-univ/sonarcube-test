#pragma once
#include "View.h"
#include "TranslationService.h"

class MultiplayerView : public View
{
	TranslationService service;
	bool startGame;
public:
	MultiplayerView();
	void draw() override;
	View* handle() override;
};