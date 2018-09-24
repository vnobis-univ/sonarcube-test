#include "StartView.h"
#include "Player.h"
#include <fstream>
#include <iostream>

int main()
{	
	setConsoleSize(50, 30);
	system("title SEA BATTLE");
	showCursor(false);
	setConsoleTextType();
	View* view = new StartView;
	while (view != nullptr)
	{
		View * newView;
		view->clean();
		system("color 3B");
		view->draw();
		view->printLogo();
		newView = view->handle();
		if (view != newView)
		{
			delete view;
			view = newView;
		}
	}
}
