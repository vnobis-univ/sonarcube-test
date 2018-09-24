#include "HighScoresView.h"
#include<fstream>
#include "StartView.h"



HighScoresView::HighScoresView(Languages l, TypeOfGame t) :
	View(l, t)
{
	ifstream highScores("HighScores.txt");
	for (int i = 0; i < size; ++i)
	{
		highScores >> arrayOfPlayers[i];
	}
}

void HighScoresView::draw()
{
	clean();
	Printer p(mainTextColor, mainBackgroundColor);
	Printer p1(textColor, mainBackgroundColor);
	if (lang == Languages::English)
	{
		printAtCenterOfLine(2, "High Scores", p, consoleWidth);
		printAtCenterOfLine(27, "Press ENTER to return to main menu", p, consoleWidth);
	}
	else
	{
		printAtCenterOfLine(2, "Рекорди", p, consoleWidth);
		printAtCenterOfLine(27, "Натисніть ENTER, щоб повернутись до головного меню", p, consoleWidth);
	}
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	for (int i = 0; i < size; ++i)
	{
		arrayOfPlayers[i].print(5 + i * 2, p1);
	}
}

View * HighScoresView::handle()
{
	int key = _getch();
	while (key)
	{
		if (key == 13)
		{
			return new StartView(lang, type);
		}
		else if (key == 27)
		{
			return nullptr;
		}
	}
}
