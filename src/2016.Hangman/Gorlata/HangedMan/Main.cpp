#include <iostream>
#include <string>
#include "View.h"
#include "MenuView.h"
#include "Field.h"
#include "LangOption.h"



using namespace std;

int main()
{
	

	setConsoleSize(670, 340);
	setlocale(LC_CTYPE, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	View* view = new MenuView;

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