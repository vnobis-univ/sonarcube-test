#pragma once
#include "ViewClasses.h"
#include "Game.h"

int counter1 = 0;

string options[4] = { "START", "HIGHSCORE TABLE", "OPTIONS", "EXIT" };

StartView::StartView(SelectedOption opt) : opt(opt){}

View* StartView::getNextView(SelectedOption selectedOption)
{
	View* view = NULL;
	switch (selectedOption)
	{
	case SelectedOption::Start:
		view = new GameView();
		break;
	case SelectedOption::HighScores:
		view = new HighScoresView();
		break;
	case SelectedOption::Options:
		view = new OptionsView();
		break;
	case SelectedOption::Exit:
		break;
	}
	return view;
}

View* StartView::handleInput()
{
	View* view = this;
	int sp = static_cast<int>(opt);
	Button but = getButton(possibleButtons, 3);
	switch (but)
	{
	case Button::UP:
		sp--;
		break;
	case Button::DOWN:
		sp++;
		break;
	case Button::ENTER:
		view = getNextView(opt);
		counter1 = 0;
		clear();
		break;
	}

	if (sp >= 0 && sp < 4)
	{
		opt = (SelectedOption)(sp);
	}

	return view;
}

void StartView::drawBackground()
{
	if (counter1 == 0)
	{
		setConsoleVisability(false);

		printerRect(0, 0, 80, 2, Printer(Color::lAqua, Color::dBlue));
		printAtMiddle(translater.getName("HangMan"), 1, Printer(Color::lBlack, Color::dBlue));

		printerRect(0, 3, 80, 18, Printer(Color::lAqua, Color::lBlue));

		printerRect(0, 19, 80, 21, Printer(Color::lAqua, Color::dBlue));
		printAtMiddle(translater.getName("@All rights reserved"), 20, Printer(Color::lBlack, Color::dBlue));

		setConsoleVisability(true);

		++counter1;
	}
}

void StartView::drawInscriptions()
{
	for (int i = 0; i < 4; ++i)
	{
		static_cast<int>(opt) == i ?
			printAtMiddle("->" + translater.getName(options[i]) + "<-", 8 + i, pPurpleBlue) :
			printAtMiddle("  " + translater.getName(options[i]) + "  ", 8 + i, pWhiteBlueBlue);
	}
}
void StartView::draw()
{
	drawBackground();
	drawInscriptions();
}

StartView::~StartView()
{
	delete[] possibleButtons;
}