#include "StartView.h"
#include "FieldView.h"
#include "DifficultyView.h"
#include "HightScoresView.h"
#include <string>
#include "Utils.h"

StartView::StartView() : selected(0) {};

void StartView::printMenu()
{
	//case selected becamed out of range after user's key press
	if (selected == 3) selected = 0;
	if (selected == -1) selected = 2;

	for (int i = 0; i < 3; ++i)
	{
		i != selected ? whiteOnBlue.MidLinePrint(i + 7, options[i]) :
			purpleOnBlue.MidLinePrint(i + 7, options[i]);
	}
}

void StartView::draw()
{
	clean();
	system("COLOR 10");

	whiteOnBlue.MidLinePrint(4, "WELCOME TO THE GREATEST TIC-TAC-TOE EVER!");
	whiteOnBlue.MidLinePrint(25, "(c) all rights reserved, 2016");

	showCursor(false);
	printMenu();
}

View* StartView::handle()
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
				nextView = new chooseDifficultyView;
			else if (selected == 1)
				nextView = new HightScoresView;
			else
				exit(0);
			break;
		}
	}

	return nextView;
}

