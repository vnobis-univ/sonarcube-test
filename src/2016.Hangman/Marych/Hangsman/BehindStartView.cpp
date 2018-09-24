#include "BehindStartView.h"
#include "Console.h"
#include "Color.h"
#include "StartView.h"
#include <conio.h>

Printer selectedMenu2(Color::LIGHT_RED, Color::BLACK);

BehindStartView::BehindStartView() : selected(0) {}
void BehindStartView::printMenu()
{
	for (int i = 0; i < 2; ++i)
	{
		int pos = 2 * i + 2;
		i == selected ? printAtCenterOfLine(pos + 15, options[i], selectedMenu2) :
			printAtCenterOfLine(pos + 15, options[i], defaultPrinter);
	}
}
void BehindStartView::draw()
{
	View::draw();
	printMenu();
}

View* BehindStartView::handle()
{
	View* nextView = this;
	bool choose = false;
	while (!choose)
	{
		switch (_getch())
		{
		case 80://Down
			selected++;
			if (selected == 2) selected = 1;
			printMenu();
			break;
		case 72://Up
			selected--;
			if (selected == -1) selected = 0;
			printMenu();
			break;
		case 13://Enter
			if (selected == 0)
			{
				setLangToEng();
				nextView = new StartView;
				choose = true;
				break;
			}
			else if (selected == 1)
			{
				setLangToUkr();
				nextView = new StartView;
				choose = true;
				break;
			}
			else
			{
				exit(0);
			}
		case 27:
			exit(0);
		}
	}
	clean();
	return nextView;
}
