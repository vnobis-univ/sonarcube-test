#include "StartView.h"
#include <windows.h>
#include "func.h"
#include "Options.h"
#include "FieldView.h"
#include "HighScoresView.h"
#include "Globals.h"

StartView::StartView()
{	
	availableOptions[0] = Options::Start;
	availableOptions[1] = Options::HighScores;
	availableOptions[2] = Options::Exit;
}

void StartView::draw()
{
	printAtCenterOfLine(3, "Tic tac toe :)", yellowSymbolsGreenBackground); 
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
			printAtCenterOfLine(10 + 2 * i, "*" + convertToString(currentOption) + "*", lightGreenSymbolsGreenBackground);
			cout << endl;
		}
		else
		{
			printAtCenterOfLine(10 + 2 * i, convertToString(currentOption), yellowSymbolsGreenBackground);
			cout << endl;
		}
	}
}

string StartView::convertToString(Options option)
{
	switch (option)
	{
	case Options::Start:
		return "Start Game";
	case Options::HighScores:
		return "High Scores";
	case Options::Exit:
		return "Exit";
	}

	return "Oops,.. out of options";
}
View* StartView::handle()
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
	}
	return newView;
}
View* StartView:: applyOption()
{
	View* view = NULL;
	switch (availableOptions[selectedOption])
	{
	case Options::Start:
		view = new FieldView();
		break;
	case Options::HighScores:
		view = new HighScoresView();
		break;
	case Options::Exit:
		view = NULL;
		break;
	}
	return view;

}