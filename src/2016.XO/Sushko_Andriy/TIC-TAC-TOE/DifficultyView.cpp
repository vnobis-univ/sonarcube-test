#include "DifficultyView.h"
#include "FieldView.h"
#include "StartView.h"

chooseDifficultyView::chooseDifficultyView() : selected(0) {}

void chooseDifficultyView::printMenu()
{
	if (selected == 2) selected = 0;
	if (selected == -1) selected = 1;

	for (int i = 0; i < 2;++i)
	{
		i == selected ? purpleOnBlue.MidLinePrint(i*2 + 7, options[i]) :
			whiteOnBlue.MidLinePrint(i*2 + 7, options[i]);
	}
}

void chooseDifficultyView::draw()
{
	clean();
	system("COLOR 10");

	whiteOnBlue.MidLinePrint(4, "Chose Difficulty level: ");
	whiteOnBlue.MidLinePrint(25, "(c) all rights reserved, 2016");

	printMenu();
}

View * chooseDifficultyView::handle()
{
	View* nextView = this;
	bool choiceMade = false;

	while (!choiceMade)
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
		case 27:
			nextView = new StartView;
			choiceMade = true;
			break;
		case 13:
			choiceMade = true;
			nextView = new FieldView((difficulty)selected);
			break;
		}
	}

	return nextView;
}
