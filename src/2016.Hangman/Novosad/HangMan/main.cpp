#include <iostream>
#include "StartView.h"
#include "HighScoresView.h"
#include "GameView.h"
#include "LevelView.h"
#include "View.h"
#include "ConsoleFunctions.h"
#include "LevelOptions.h"
#include <fstream>
#include <windows.h>
#include "Globals.h"
#include <stdio.h>
#include <string.h>
#include "TranslationService.h"
using namespace std;

int main()
{
	system("color 2E");
	ifstream in("Lines.txt");
	readLinesFromFile(in);
	showConsoleCursor(false);
	setConsoleToLucidaConsole();
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream file("Highscores.txt");
	readPlayersFromFile(file);
	setConsoleSize(50, 30);
	View* view = new StartView();
	while (view != NULL)
	{
		View* newView;
		view->clean();
		view->draw();
		newView = view->handle();

		if (view != newView)
		{
			delete view;
			view = newView;
		}
	}
}