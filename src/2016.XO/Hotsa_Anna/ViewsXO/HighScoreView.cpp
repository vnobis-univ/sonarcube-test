#include "HighScoreView.h"
#include "ResultView.h"
#include "Utils.h"
#include "Player.h"
#include "StartView.h"
#include <fstream>
#include "ExternVar.h"

HighScoreView::HighScoreView() {}
void typeName();
void HighScoreView::draw()
{
	system("cls");
	typeName();
	Printer prButton(Color::BLUE, Color::LIGHT_WHITE);
	Printer prScore(Color::BLUE, Color::GRAY);
	printAtCenter(9, "PLAYER       SCORE", prScore);
	string names[5];
	for (int i = 0; i < 5; i++)
	{
		moveCursorTo(20, 11 + i);
		prScore << to_string(i + 1) << ".";
		moveCursorTo(22, 11 + i);
		prScore << playersList[i].getName();
		moveCursorTo(36, 11 + i);
		prScore << to_string(playersList[i].getScore());
		names[i] = playersList[i].getName();
	}
	for (int i = 0; i < 5; i++)
	{
		int k = names[i].size();
		moveCursorTo(22 + k, 11 + i);
		for (int i = 22 + k; i < 36; i++)
		{
			prScore << ".";
		}
	}
	printAtCenter(17, "[ PRESS ENTER TO BACK TO MENU ]", prButton);
}

View* HighScoreView ::handle()
{
	showCursor(false);
	int button;
	while (true)
	{
		button = _getwch();
		switch (button)
		{
		case 13:
		{
			View * nextView = new StartView;
			return nextView;
		}
		break;
		default:
		{
			return this;
		}
		}
	}
}