#pragma once
#include "Classes.h"
int counter = 0;

string options[3] = { "START GAME", "HIGHSCORES", "EXIT" };

StartView::StartView(SelectedOption opt) : opt(opt){}

View* StartView::getNextView(SelectedOption selectedOption)
{
	View* view = NULL;
	switch (selectedOption)
	{
	case SelectedOption::Start:
		view = new FieldView();
		break;
	case SelectedOption::HighScores:
		view = new HighScoresView();
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
	Button but = getButton(possibleButtons, StartView::size);
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
		counter = 0;
		clear();
		break;
	}

	if (sp >= 0 && sp < 3)
	{
		opt = (SelectedOption)(sp);
	}

	return view;
}

void StartView::drawBackground()
{
	if (counter == 0)
	{
		setConsoleVisability(false);

		printerRect(5, 0, 75, 2, Printer(Color::lAqua, Color::dBlue));
		printAtMiddle("Tic-tac-toe", 1, Printer(Color::lBlack, Color::dBlue));

		printerRect(0, 3, 80, 18, Printer(Color::lAqua, Color::lBlue));

		printerRect(5, 19, 75, 21, Printer(Color::lAqua, Color::dBlue));
		printAtMiddle("Created by Kir Oleg", 20, Printer(Color::lBlack, Color::dBlue));
		
		setConsoleVisability(true);

		++counter;
	}
}

void StartView::drawInscriptions()
{
	for (int i = 0; i < 3; ++i)
	{
		static_cast<int>(opt) == i ?
			printAtMiddle("->" + options[i] + "<-", 8 + i, pPurpleBlue) :
			printAtMiddle("  " + options[i] + "  ", 8 + i, pWhiteBlueBlue);
	}
}
void StartView::draw()
{
	drawBackground();
	drawInscriptions();
	setCursor(0, 0);
}

StartView::~StartView()
{
	delete[] possibleButtons;
}