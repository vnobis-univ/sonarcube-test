#include "Classes.h"
#include "ConsoleTools.h"
#include "SavingWinners.h"

SavingWinners saver;

int main()
{
	//loading data from file
	saver.loadHighScores();

	//setting console options
	setConsole(80, 22.5); // 800 * 450 - size of the console in pixels what is roughly 80 * 21 in cursors

	//game process code below
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