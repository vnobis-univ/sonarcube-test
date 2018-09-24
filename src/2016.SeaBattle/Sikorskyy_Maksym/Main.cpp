#include "ViewClasses.h"
#include "ConsoleTools.h"
#include "SavingWinners.h"
#include "Translating.h"
#include "OptionModes.h"
#include "Game.h"

SavingWinners saver;
Language currLang = Language::Ukrainian;
Translating translater;

int main()
{
	SetConsoleTitle("Sea Battle");
	setConsole(80, 22);
	saver.loadHighScores();
	View* view = new StartView();
	while (view != nullptr)
	{
		View* newView;

		view->draw();
		showConsoleCursor(false);

		newView = view->handleInput();
		if (view != newView)
		{
			delete view;
			view = newView;
		}
	}
}