#include "View.h"
#include <iostream>
#include "Console.h"
#include "BehindStartView.h"

using namespace std;

int main()
{
	setConsoleSize(80, 40);

	View* view = new BehindStartView();
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