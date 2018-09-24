#include "StartView.h"
#include "Printer.h"
#include <conio.h>
#include "FieldView.h"
#include "Highscores.h"
#include "Colors.h"

string headers[3] = { "Start", "Highscores", "Exit" };

Printer menu(Color::LightGray, Color::Black);
Printer selectedMenu(Color::LightGray, Color::Brown);

StartView::StartView():selected(0){}

void StartView::printMenu()
{
	for (int i = 0; i < 3; ++i)
	{
		int pos = 3 * i;
		i == selected ? printInCenter(pos + 8, headers[i], selectedMenu) :
			printInCenter(pos + 8, headers[i], menu);
	}
}

void StartView::draw()
{
	View::draw();
	printMenu();
}

View* StartView::handle()
{
	View *nextView = this;
	bool chosen = false;
	while (!chosen)
	{
		switch (_getch())
		{
		case 80:
			selected++;
			if (selected == 3)
			{
				selected = 2;
			}
			printMenu();
			break;

		case 72:
			selected--;
			if (selected == -1)
			{
				selected = 0;
			}
			printMenu();
			break;
		case 13:
			if (selected == 0)
			{
				nextView = new FieldView;
				chosen = true;
				break;
			}
			else if (selected == 1)
			{
				nextView = new HighScoresView;
				chosen = true;
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