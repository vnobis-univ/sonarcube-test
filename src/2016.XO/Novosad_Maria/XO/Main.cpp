#include <iostream>
#include "StartView.h"
#include "HighScoresView.h"
#include "FieldView.h"
#include "ResultView.h"
#include "View.h"
#include "ConsoleFunctions.h"
#include <fstream>
#include <windows.h>
#include "Globals.h"
using namespace std;

Player* readPlayersFromFile()
{
	ifstream in("Text.txt");
	for (int i = 0; i < 6; i++)
	{
		in >> global_players[i];
	}
	return global_players;
}

int main()
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	setConsoleSize(50, 30);
	showConsoleCursor(false);
	readPlayersFromFile();
	View* view = new StartView();
	while (view != NULL)
	{
		SetConsoleTextAttribute(hConsole, (14 + 2 * 16));
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
	return 0;
}

