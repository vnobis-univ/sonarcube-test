#include "Printer.h"
#include "HelpView.h"
#include "Console.h"
#include <conio.h>
#include "ChooseComplexView.h"
#include "FieldView.h"

Printer selectedMenu4(Color::LIGHT_RED, Color::BLACK);
void HelpView::print()
{
	if (language == "Eng")
	{
		printAtCenterOfLine(10, "Please enter CAPS LOCK", defaultPrinter);
		printAtCenterOfLine(12, "Please look at your language at your PC", defaultPrinter);
		printAtCenterOfLine(13, "Language must be ENGLISH", defaultPrinter);
		printAtCenterOfLine(25, "Continue", selectedMenu4);
	}
	else if (language == "Ukr")
	{
		printAtCenterOfLine(10, "Натиснiть CAPS LOCK", defaultPrinter);
		printAtCenterOfLine(12, "Перевiрте вашу розкладку на ПК", defaultPrinter);
		printAtCenterOfLine(13, "Розкладка повинна бути УКРАЇНСЬКОЮ", defaultPrinter);
		printAtCenterOfLine(25, "Продовжити", selectedMenu4);
	}
}
void HelpView::draw()
{
	View::draw();
	print();
}

View* HelpView::handle()
{
	View* nextView = this;
	bool choose = false;
	while (!choose)
	{
		switch (_getch())
		{
		case 27:
			nextView = new ChooseComplexView;
			choose = true;
			break;
		case 13:
			nextView = new FieldView;
			choose = true;
			break;
		}
	}
	return nextView;
}
