#include <Windows.h>
#include <string>
#include "Console.h"
#include "View.h"
#include "StartView.h"
#include <conio.h>

int main()
{
	setConsoleSize(50, 25);
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