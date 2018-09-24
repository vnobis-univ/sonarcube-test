#include "View.h"
#include <iostream>
#include "Console.h"
#include "Button.h"
#include "StartView.h"

using namespace std;

int main()
{
	setConsoleSize(130, 50);

	View* view = new StartView();
	while (view != NULL)
	{
		View* newView;

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