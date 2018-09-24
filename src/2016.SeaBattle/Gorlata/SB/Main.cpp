#include <iostream>
#include "View.h"
#include "MenuView.h"
#include "LanguageSelection.h"
#include "Utils.h"
#include <ctime>


using namespace std;

int main()
{

		
	setConsoleSize(670, 340);
	setlocale(LC_CTYPE, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));


	View* view = new MenuView;

	while (view != nullptr)
	{
		View* newView;

		system("CLS");
		view->draw();

		newView = view->handle();

		if (view != newView)
		{
			delete view;
			view = newView;
		}
	}

	system("pause");
}