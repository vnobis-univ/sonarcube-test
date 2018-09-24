#include "Console_.h"
#include "View.h"
#include "StartView.h"

int main()
{
	enableUkrainianLang();
	setConsoleSize(52, 30);
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