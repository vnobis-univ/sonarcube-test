#include "HighScoreView.h"
#include "ConsoleUtils.h"
#include "Player.h"
#include "Printers.h"
#include "StartView.h"
#include <fstream>

HighScoreView::HighScoreView() {}

void typeName();
void HighScoreView::draw()
{
	typeName();
	printAtCenter(7, "PLAYER       LEVEL       SCORE     GUESSED LETTERS", blueTextGrayBG);
	for (int i = 0; i < numOfPlayers; i++)
	{
		moveCursorTo(4, 9 + i);
		blueTextGrayBG << playersList[i].getName();
		moveCursorTo(17, 9 + i);
		blueTextGrayBG << playersList[i].getLevel();
		moveCursorTo(30, 9 + i);
		blueTextGrayBG << to_string(playersList[i].getScore());
		moveCursorTo(46, 9 + i);
		blueTextGrayBG << to_string(playersList[i].getGuessedLetters());
	}
	printAtCenter(22, "[-PRESS ESC TO RETURN TO MENU-]", blueTextGrayBG);
}

View* HighScoreView::handle()
{
	showCursor(false);
	int button;
	while (true)
	{
		button = _getwch();
		switch (button)
		{
		case KEY_ESCAPE:
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