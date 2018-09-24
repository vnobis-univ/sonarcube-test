#include <iostream>
#include "LevelView.h"
#include "Globals.h"
#include "ConsoleFunctions.h"
#include "GameView.h"
#include "StartView.h"
using namespace std;

LevelView::LevelView()
{
	service = TranslationService(language);
	options[0] = LevelOptions::Easy;
	options[1] = LevelOptions::Middle;
	options[2] = LevelOptions::Hard;
}

void LevelView::draw()
{
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
		LevelOptions currentOption = options[i];
		if (options[selectedOption] == currentOption)
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
}

View* LevelView::handle()
{
	View* newView = this;
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
	case KEY_ESCAPE:
	{
		newView = new StartView();
		break;
	}
	}

	return newView;
}

View* LevelView::applyOption()
{
	View* view = NULL;
	switch (options[selectedOption])
	{
	case LevelOptions::Easy:
		view = new GameView(LevelOptions::Easy);
		break;
	case LevelOptions::Middle:
		view = new GameView(LevelOptions::Middle);
		break;
	case LevelOptions::Hard:
		view = new GameView(LevelOptions::Hard);
		break;
	} 
	return view;
}