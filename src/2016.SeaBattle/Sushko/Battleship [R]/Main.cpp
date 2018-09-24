#include <Windows.h>
#include "ConsoleUtils.h"
#include "StartView.h"

int main() 
{
	SetConsoleTitle("Battleship online");
	setConsoleSize(500, 650);
	removeScrollbar();
	disableResizing();
	enableUkrainian();
	showCursor(false);
	
	View* view = new EngStartView();
	while (view != nullptr) {

		View* newView;

		system("CLS"), system("COLOR 31");

		view->draw();
		newView = view->handle();

		if (view != newView) {
			delete view;
			view = newView;
		}
	}

	return 0;
}