#include "ViewClasses.h"
#include "ConsoleTools.h"
#include "SavingWinners.h"
#include "Translating.h"
#include "OptionModes.h"
#include "Game.h"

SavingWinners saver;
Language currLang = Language::English;
Sex currSex = Sex::Male;
Translating translater;

int main()
{
	//setting console options
	setConsole(80, 22);
	//loading data from file
	saver.loadHighScores();


	//game process code below
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