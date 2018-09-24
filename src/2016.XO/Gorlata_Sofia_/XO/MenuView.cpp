#include "MenuView.h"
#include <iostream>
#include "Utils.h"
#include "Field.h"
#include "HighScore.h"

using namespace std;

void MenuView::printMenu()
{
	system("cls");
	system("color 90");

	whiteOnBlue.printOnCenter(6, " MENU: ");
	whiteOnBlue.printOnCenter(7, "~~~~~~~");

	if (selected == 3)
	{
			selected = 0;
		}
		if (selected == -1)
		{
			selected = 2;
		}

		for (int i = 0; i < 3; ++i)
		{
			selected != i ? whiteOnBlue.printOnCenter(i + 10, option[i]) : darkBlueOnBlue.printOnCenter(i + 10, "> " + option[i] + " <");
		}

}

MenuView::MenuView(): selected(0) {}

void MenuView::draw()
{	
	printMenu();
}

View* MenuView::handle()
{
	View* nextView = this;
	bool userChoose = false;

	while (!userChoose)
	{
		switch (_getwch())
		{
		case 72:
			selected--;
			printMenu();
			break;
		case 80:
			selected++;
			printMenu();
			break;
		case 13:
			userChoose = true;
			if (selected == 0)
			{
				nextView = new Field;
			}
			else if (selected == 1)
			{
				nextView = new HighScore();
			}
			else
			{
				exit(0);
			}
			break;
		}
	}

	return nextView;
}
