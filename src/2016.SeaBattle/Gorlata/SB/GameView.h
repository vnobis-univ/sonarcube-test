#pragma once
#include "Field.h"
#include "View.h"


class GameView : public View 
{

	Field myField;
	Field enemyField;
	
	
public:
	virtual void draw();
	virtual View* handle();



	GameView(Language m_lang);
};