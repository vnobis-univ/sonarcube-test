#include "StartView.h"

using namespace std;

int main()
{
	View* view = new StartView;
	
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

	return 0;
}