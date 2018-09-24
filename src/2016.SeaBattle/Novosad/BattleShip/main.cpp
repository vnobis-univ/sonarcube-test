#pragma once
#include <fstream>
#include "View.h"
#include "StartView.h"
#include "ConsoleFunctions.h"
#include "Globals.h"

using namespace std;

int main()
{
	ifstream keys("Keys.txt");
	ifstream players("Players.txt");
	readKeysFromFile(keys);
	readPlayersFromFile(players);
	showConsoleCursor(false);
	setConsoleToLucidaConsole();
	setConsoleSize(54, 30);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("Color 2E");

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
	
	return 0;
}