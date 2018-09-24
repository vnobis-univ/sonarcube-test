#include "ViewClasses.h"
#include "ConsoleTools.h"
#include "SavingWinners.h"
#include "Dictionary.h"
#include <locale>
#include "Translating.h"
#include <codecvt>
#include <conio.h>
#include <iostream>

SavingWinners saver;
Language currLang = Language::English;
DifficultyModes currMode = DifficultyModes::Easy; 
Dictionary dict; 
Translating transform;

int main()
{
	SetConsoleTitle("Hangman");
	setConsole(900, 420);;
	
	
	saver.loadHighScores();
	dict.loadWords(); 
	

	
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