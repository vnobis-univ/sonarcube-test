#include "Printer.h"
#include "StartView.h"
#include "Console.h"
#include <conio.h>
#include "FieldView.h"
#include "Highscores.h"
#include "Color.h"

Printer menu(ConsoleColor::LightGray, ConsoleColor::DarkGray);
Printer selectedMenu(ConsoleColor::LightGray, ConsoleColor::Red);

StartView::StartView() : selected(0) {}
void StartView::printMenu()
{
	for (int i = 0; i < 3; ++i)
	{
		int pos = 3*i;
		i == selected ? printTextOnTheCenter(pos + 5, options[i], selectedMenu) :
			printTextOnTheCenter(pos + 5, options[i], menu);
	}
}
void StartView::draw()
{
	View::draw();
	printMenu();
}
View* StartView::handle()
{
	View* nextView = this;
	bool choose = false;
	while (!choose)
	{
		switch (_getch())
		{
		case 80://Down
			selected++;
			if (selected == 3) selected = 2;
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
				nextView = new ComplexityView();
				choose = true;
				break;
			}
			else if (selected == 1)
			{
				nextView = new HighscoresView;
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
	system("cls");
	return nextView;
}
