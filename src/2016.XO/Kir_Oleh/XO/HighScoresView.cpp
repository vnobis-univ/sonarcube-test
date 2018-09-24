#pragma once
#include "Classes.h"
#include "SavingWinners.h"

View* HighScoresView::handleInput()
{
	wait();
	clear();
	return new StartView(SelectedOption::HighScores);
}

void HighScoresView::drawBackButton()
{
	SelectObject(dc, penBlue);
	SelectObject(dc, brushOrange);
	Rectangle(dc, 345, 250, 455, 290);

	SelectObject(dc, brushBlack);
	Rectangle(dc, 350, 255, 450, 285);

	setCursor(36, 13);
	pPurpleBlack.print("->BACK<-");
}


void HighScoresView::drawInscriptions()
{
	setCursor(25, 6);
	cout << "PLAYER" << endl;

	setCursor(50, 6);
	cout << "SCORE" << endl;
}

void HighScoresView::drawUserResults()
{
	for (int i = 0; i < hsSize; ++i)
	{
		setCursor(25, 7 + i);
		cout << saver[i].name;
		setCursor(52, 7 + i);
		cout << saver[i].scores;
	}
}

void HighScoresView::draw()
{
	drawFrame();
	drawInscriptions();
	drawUserResults();
	drawBackButton();
	setCursor(0, 0);
}
