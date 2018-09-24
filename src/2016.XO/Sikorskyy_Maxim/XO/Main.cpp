#include "Classes.h"
#include "ConsoleTools.h"
#include "SetRecord.h"

SavingWinners buff;

int main()
{
	
	

	SetConsoleTitle("Tic-Tac-toe");
	setConsole(600, 450); 

	buff.loadScores();

    View* view = new StartView();
	while (view != NULL)
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