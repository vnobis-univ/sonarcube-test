#include <iostream>
#include "ConsoleUtils.h"
#include "MenuView.h"

using namespace std;

int main() {

	showCursor(false);
	setConsoleSize(50, 120);
	restrictResize();
	enableUkrainian();

	View* view = new EngMenu;
	while (view != nullptr) {

		View* newView;

		system("CLS"), system("COLOR 5B");

		view->draw();
		newView = view->handle();

		if (view != newView) {
			delete view;
			view = newView;
		}
	}

	system("PAUSE");
}