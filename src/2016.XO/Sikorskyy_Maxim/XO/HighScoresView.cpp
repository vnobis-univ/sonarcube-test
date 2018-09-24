#pragma once
#include "Classes.h"
#include "SetRecord.h"

View* HighScoresView::handleInput()
{
	wait();
	clear();
	return new StartView(SelectedOption::HighScores);
}

void HighScoresView::drawBackButton()
{
	setCursor(23, 13);
	Printer(Color::dRed,Color::dYellow).print("-> BACK <-");
}


void HighScoresView::drawStrings()
{
	setCursor(15, 3);
	Printer(Color::dBlack, Color::dYellow).print("NAME");

	setCursor(35, 3);
	Printer(Color::dBlack, Color::dYellow).print("RECORD");
}

void HighScoresView::drawUserResults()
{
	
	
	for (int i = 0; i < hsSize; ++i)
	{
		setCursor(15, 5 + i);
		
		
		Printer(Color::dBlack, Color::dYellow).print(buff[i].name);
		setCursor(38, 5 + i);
		Printer(Color::dBlack, Color::dYellow).print(to_string(buff[i].scores));
		
	}
}

void HighScoresView::draw()
{
	printRect(0, 0, 60, 21, Printer(Color::lBlack, Color::dYellow));
	printRect(0, 0, 60, 2, Printer(Color::lBlack, Color::dRed));
	printAtMiddle("Tic-tac-toe", 1, Printer(Color::dBlack, Color::dRed));


	drawStrings();
	drawUserResults();
	drawBackButton();
	setCursor(0, 0);
}
