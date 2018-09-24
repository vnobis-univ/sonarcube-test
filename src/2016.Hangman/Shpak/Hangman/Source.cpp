#include "ConsoleManipulators.h"
#include "GreetingView.h"

int main()
{
	coolConsoleStuff();
	
	View* view = new GreetingView();

	while (view != nullptr)
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