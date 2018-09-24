#pragma once

#include "HighScoreView.h"
#include "ConsoleProperties.h"
#include "StartView.h"

#include <conio.h>

HighScoreView::HighScoreView()
{
	markUpText.push_back("HIGH SCORES");
	markUpText.push_back("Name:            Score:   Letters: Language:      Level:    ");
	markUpText.push_back("Press any key to continue");
}

void HighScoreView::draw()
{
	clear();
	configure();

	setCursorAt(0, 1);

	printAtCenter(markUpText[0], headline);

	setCursorAt(0, 3);
	techData.print(markUpText[1]);
	

	for (size_t i = 0; i < options.getRecords().size(); ++i)
	{
		setCursorAt(0, 5 + i);

		vector<Player> buffer = options.getRecords();

		string name = toString(buffer[i].nickname) + string(17 - toString(buffer[i].nickname).size(), ' ');
		string score = toString(buffer[i].score) + string(9 - toString(buffer[i].score).size(), ' ');
		string letters = toString(buffer[i].numLetters) + string(9 - toString(buffer[i].numLetters).size(), ' ');
		string language;
		string level;

		
		if (buffer[i].langUsed == Language::ENGLISH)
		{
			if (options.getLanguage() == Language::ENGLISH)
			{
				language = "English        ";
			}
			else
			{
				language = "Англійська     ";
			}
		}
		else
		{
			if (options.getLanguage() == Language::ENGLISH)
			{
				language = "Ukrainian      ";
			}
			else
			{
				language = "Українська     ";
			}
		}
		

		if (buffer[i].topLevel == Difficulty::EASY)
		{
			if (options.getLanguage() == Language::ENGLISH)
			{
				level = "Easy      ";
			}
			else
			{
				level = "Легкий    ";
			}
		}
		else if (buffer[i].topLevel == Difficulty::MIDDLE)
		{
			if (options.getLanguage() == Language::ENGLISH)
			{
				level = "Medium    ";
			}
			else
			{
				level = "Середній  ";
			}
		}
		else
		{
			if (options.getLanguage() == Language::ENGLISH)
			{
				level = "Hard      ";
			}
			else
			{
				level = "Складний  ";
			}
		}

		stats.print(name + score + letters + language + level);
	}
}

View* HighScoreView::handle()
{
	setCursorAt(0, cursor.Y + 2);

	techData.print(markUpText[2]);

	_getch();

	return new StartView;
}