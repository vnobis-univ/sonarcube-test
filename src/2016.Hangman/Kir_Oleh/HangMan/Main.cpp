#include "ViewClasses.h"
#include "ConsoleTools.h"
#include "SavingWinners.h"
#include "Dictionary.h"
#include "Translating.h"
#include "OptionModes.h"

SavingWinners saver;
Language currLang = Language::English;
Difficulty currDifficulty;
Sex currSex = Sex::Male;
Dictionary dict; 
Translating translater;

int main()
{
	//setting console options
	setConsole(80, 22);
	//loading data from file
	saver.loadHighScores();
	//loading words from .txt
	dict.loadWords(); 


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