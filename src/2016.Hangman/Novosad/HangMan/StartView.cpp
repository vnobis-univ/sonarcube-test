#include "StartView.h"
#include <windows.h>
#include "Options.h"
#include "GameView.h"
#include "HighScoresView.h"
#include "Globals.h"
#include "LevelView.h"

StartView::StartView()
{
	service = TranslationService(language);
	availableOptions[0] = Options::Start;
	availableOptions[1] = Options::HighScores;
	availableOptions[2] = Options::Exit;
}

void StartView::draw()
{
	printAtCenterOfLine(3, service.getWord("hangman"), lightGreenSymbolsGreenBackground);
	setCursoreAtPosition(1, 1);
	for (int i = 0; i < 48; i++)
	{
		cout << "-";
	}
	setCursoreAtPosition(1, 28);
	for (int i = 0; i < 48; i++)
	{
		cout << "-";
	}
	for (int i = 0; i < 26; i++)
	{
		setCursoreAtPosition(1, 2 + i);
		cout << "|";
	}
	for (int i = 0; i < 26; i++)
	{
		setCursoreAtPosition(48, 2 + i);
		cout << "|";
	}
	for (int i = 0; i < 3; ++i)
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
	printAtCenterOfLine(26, service.getWord("press_whitespace_to_switch_lang"), lightGreenSymbolsGreenBackground);
}

string StartView::convertToString(Options option)
{
	switch (option)
	{
	case Options::Start:
		return "start_game";
	case Options::HighScores:
		return "highscores";
	case Options::Exit:
		return "exit";
	}
}

View* StartView::handle()
{
	View* newView = this;
	ifstream file1("HighscoresUkr.txt");
	ifstream file2("Highscores.txt");
	int key = _getch();
	switch (key)
	{
	case KEY_DOWN:
	{
		if (selectedOption != 2)
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
			selectedOption = 2;
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
	case KEY_WHITESPACE: 
	{
		if (language == Language::ENG)
		{
			readPlayersFromFile(file1);
			language = Language::UKR;
			service = TranslationService(Language::UKR);
		}
		else
		{
			readPlayersFromFile(file2);
			language = Language::ENG;
			service = TranslationService(Language::ENG);
		}
	}
	}
	return newView;
}

View* StartView::applyOption()
{
	View* view = NULL;
	switch (availableOptions[selectedOption])
	{
	case Options::Start:
		view = new LevelView();
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
