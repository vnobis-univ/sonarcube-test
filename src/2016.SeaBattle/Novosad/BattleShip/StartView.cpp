#include "StartView.h"
#include "Options.h"
#include "FieldView.h"
#include "HighScoresView.h"
#include "Globals.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include "ConsoleFunctions.h"
#include "MultiplayerView.h"

StartView::StartView()
{
	service = TranslationService(language);
	availableOptions[0] = Options::SinglePlayer;
	availableOptions[1] = Options::Multiplayer;
	availableOptions[2] = Options::HighScores;
	availableOptions[3] = Options::Exit;
}

void StartView::draw()
{
	printAtCenterOfLine(3, service.getWord("ship_battle"), yellowSymbolsGreenBackground);
	for (int i = 0; i < 4; ++i)
	{
		Options currentOption = availableOptions[i];
		if (availableOptions[selectedOption] == currentOption)
		{
			printAtCenterOfLine(10 + 2 * i, "*" + service.getWord(convertToString(currentOption)) + "*", lightGreenSymbolsGreenBackground);
			cout << endl;
		}
		else
		{
			printAtCenterOfLine(10 + 2 * i, service.getWord(convertToString(currentOption)), yellowSymbolsGreenBackground);
			cout << endl;
		}
	}
	printAtCenterOfLine(26, service.getWord("press_whitespace_to_switch_lang"), yellowSymbolsGreenBackground);
}

string StartView::convertToString(Options option)
{
	switch (option)
	{
	case Options::SinglePlayer:
		return "single_player_game";
	case Options::Multiplayer:
		return "multiplayer_game";
	case Options::HighScores:
		return "highscores";
	case Options::Exit:
		return "exit";
	default:
		return "";
	}
}

View* StartView::handle()
{
	View* newView = this;
	ifstream ukrHighscores("PlayersUkr.txt");
	ifstream engHighscores("Players.txt");
	int key = _getch();
	switch (key)
	{
	case KEY_DOWN:
	{
		if (selectedOption != 3)
		{
			++selectedOption;
		}
		else
		{
			selectedOption = 0;
		}
		break;
	}
	case KEY_UP:
	{
		if (selectedOption == 0)
		{
			selectedOption = 3;
		}
		else
		{
			--selectedOption;
		}
		break;
	}
	case KEY_ENTER:
	{
		newView = applyOption();
		break;
	}
	case KEY_WHITESPACE: // do something with this later!!!
		if (language == ENG)
		{
			readPlayersFromFile(ukrHighscores);
			language = UKR;
			service = TranslationService(UKR);
		}
		else
		{
			readPlayersFromFile(engHighscores);
			language = ENG;
			service = TranslationService(ENG);
		}
		break;
	}

	return newView;
}

View* StartView::applyOption()
{
	View* view = NULL;

	switch (availableOptions[selectedOption])
	{
	case Options::SinglePlayer:
		view = new FieldView(false, true, "", 0);
		break;
	case Options::Multiplayer:
		view = new MultiplayerView();
		break;
	case Options::HighScores:
		view = new HighscoresView();
		break;
	case Options::Exit:
		view = NULL;
		break;
	}

	return view;
}
