#include "MenuView.h"
#include "Field.h"
#include <string>
#include "Utils.h"
#include "Printer.h"
#include "HighScore.h"
#include "Result.h"
using namespace std;

int main() 
{
	
	setConsoleSize(670, 380);

	
	/*Field field;
	field.draw();*/
	
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
	
	
	system("pause");

}