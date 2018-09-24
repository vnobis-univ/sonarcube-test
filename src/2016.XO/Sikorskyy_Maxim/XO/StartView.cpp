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
	Button buttonReader = getButton(possibleButtons, StartView::size);
	switch (buttonReader)
	{
	case Button::UP:
		 if (sp == 0) sp = 2;
		 else sp--;
		 break;
	case Button::DOWN:
		if (sp == 2) sp = 0;
		else sp++;
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
		ConsoleVisible(false);
	
		printRect(0, 0, 60, 21, Printer(Color::lBlack, Color::dYellow));
		printRect(0, 0, 60, 2, Printer(Color::lBlack, Color::dRed));
		printAtMiddle("Tic-tac-toe", 1, Printer(Color::dBlack, Color::dRed));

		ConsoleVisible(true);

		++counter;
	}
}

void StartView::drawStrings()
{
	for (int i = 0; i < 3; ++i)
	{
		static_cast<int>(opt) == i ?
			
			printAtMiddle("-> " + options[i] + " <-", 8 + i, Printer(Color::dRed, Color::dYellow)) :
			printAtMiddle("   " + options[i] + "   ", 8 + i, Printer(Color::dBlack, Color::dYellow));
	}
}
void StartView::draw()
{
	drawBackground();
	drawStrings();
	setCursor(0, 0);
}

StartView::~StartView()
{
	delete[] possibleButtons;
}