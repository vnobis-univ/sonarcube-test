#include <iostream>
#include "StartView.h"
#include "HighScoreView.h"
#include "FieldView.h"
#include "ResultView.h"
using namespace std;

int main()
{
	setConsoleSize(57, 30);
	SetConsoleTextAttribute(hConsole, 11 * 10 + 9);
	showCursor(false);
	View* view = new StartView;	
	while (view != nullptr)
	{
		View * newView;
		view -> draw();
		newView = view->handle();

		if (view != newView)
		{
			delete view;
			view = newView;
		}
	}

	system("pause");
	return 0;
}