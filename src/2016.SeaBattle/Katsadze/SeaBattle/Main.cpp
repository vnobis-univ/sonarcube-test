#include "View.h"
#include "StartView.h"

int main()
{
	setConsoleSize(100,33);
	
	
	View* view = new StartView;
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