#include <Windows.h>
#include <string>
#include "Console.h"
#include "View.h"
#include "StartView.h"
#include <conio.h>

int main()
{
	setConsoleSize(54, 25);
	dontAllowToChangeSize();
	if (consoleHeight < 23)
	{
		cout << "Height of console must be bigger than 22\n";
		system("pause");
		return 0;
	}
	if (consoleWidth < 25)
	{
		cout << "Width of console must be bigger than 25\n";
		system("pause");
		return 0;
	}
	View *view = new StartView;
	while (view != nullptr)
	{
 		view->draw();
		View* newView = view->handle();
		if (newView != view)
		{
			delete view;
			view = newView;
		}
	}
}