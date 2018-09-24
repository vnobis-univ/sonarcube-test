#pragma once

#include "HighScoreView.h"
#include "ConsoleProperties.h"
#include "StartView.h"

#include <conio.h>

HighScoreView::HighScoreView()
{
	windowLanguage = Language::ENGLISH;

	markUpText.push_back("HIGH SCORES");
	markUpText.push_back("Name             Score    Cells    Mode        "); // scoreboard layout
	markUpText.push_back("Press any key to continue...");
}

void HighScoreView::draw()
{
	clear();
	configure();

	setCursorAt(0, 1);

	printAtCenter(markUpText[0], headline); // print "HIGH SCORES"

	setCursorAt(CONSOLE_WIDTH / 5, 3);
	printAtCenter(markUpText[1], techData); // prints scoreboard layout

	vector<PlayerData> buffer = options.records;

	// works out every record and depicts it due to the scoreboard layout
	for (size_t i = 0; i < buffer.size(); ++i)
	{
		setCursorAt(CONSOLE_WIDTH/5, 5 + i);

		string nickName = buffer[i].nickname + string(17 - buffer[i].nickname.size(), ' ');
		string playerScore = toString(buffer[i].score) + string(9 - toString(buffer[i].score).size(), ' ');
		string playerCells = toString(buffer[i].numOfCells) + 
									  string(9 - toString(buffer[i].numOfCells).size(), ' ');
		string playerMode;

		if (buffer[i].playerMode == Mode::COMPUTER)
		{
			if (windowLanguage == Language::ENGLISH)
			{
				playerMode = "Computer    ";
			}
			else
			{
				playerMode = "Комп'ютер   ";
			}
		}
		else
		{
			if (windowLanguage == Language::ENGLISH)
			{
				playerMode = "Multiplayer ";
			}
			else
			{
				playerMode = "Мультиплеєр ";
			}
		}

		printAtCenter(nickName + playerScore + playerCells + playerMode, stats);
	}
}

View* HighScoreView::handle()
{
	setCursorAt(CONSOLE_WIDTH/5, cursor.Y + 2);

	printAtCenter(markUpText[2], techData);

	_getch();

	return new StartView();
}