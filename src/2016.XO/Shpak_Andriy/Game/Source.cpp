#include "ConsoleManipulators.h"
#include "View.h"
#include "StartView.h"
#include <iostream>

int main() 
{
	setConsoleSize(65, 25);


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
}
