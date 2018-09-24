#include "ModeView.h"
#include "GameView.h"
ModesView::ModesView(Languages l, TypeOfGame t) : View(l, t)
{
	arrayOfOptions = new string[amountOfOptions];
	if (lang == Languages::English)
	{
		arrayOfOptions[0] = "Play with computer";
		arrayOfOptions[1] = "Play with another player";
		arrayOfOptions[2] = "Return to main menu";
	}
	else
	{
		arrayOfOptions[0] = "Гра з крмп'ютером";
		arrayOfOptions[1] = "Гра з іншим гравцем";
		arrayOfOptions[2] = "Повернутись до головного меню";
	}
	selectedOption = arrayOfOptions[0];
}

void ModesView::draw()
{
	clean();
	for (size_t i = 0; i < amountOfOptions; ++i)
	{
		if (arrayOfOptions[i] == selectedOption)
		{
			Printer p(textColor, mainBackgroundColor);
			printAtCenterOfLine(10 + 2 * i, "* " + arrayOfOptions[i] + " *", p, consoleWidth);
		}
		else
		{
			Printer p(mainTextColor, mainBackgroundColor);
			printAtCenterOfLine(10 + 2 * i, arrayOfOptions[i], p, consoleWidth);
		}
	}

	Printer p(textColor, mainBackgroundColor);
	if (lang == Languages::English)
	{
		printAtCenterOfLine(2, "Choose how to play", p, consoleWidth);
	}
	else
	{
		printAtCenterOfLine(2, "Виберіть, як грати", p, consoleWidth);
	}
}
int ModesView::positionOfselectedOption()
{
	for (size_t i = 0; i < amountOfOptions; ++i)
	{
		if (arrayOfOptions[i] == selectedOption)
		{
			return i;
		}
	}
}

View * ModesView::nextView()
{
	View * nextV = this;
	if (selectedOption == arrayOfOptions[2])
	{
		nextV = new StartView(lang, type);
	}
	else if (selectedOption == arrayOfOptions[0])
	{
		nextV = new GameView(lang, type);
	}
	/*else if (selectedOption == arrayOfOptions[1])
	{
		dif = Medium;
		nextV = new GameView(lang, dif);
	}
	else
	{
		dif = Hard;
		nextV = new GameView(lang, dif);
	}*/
	return nextV;
}

View * ModesView::handle()
{
	int key = _getch();
	while (key)
	{
		if (key == 224)//if arrow key was pressed
		{
			key = _getch();
		}
		switch (key)
		{
		case(13): // Enter key
		{
			return nextView();
		}
		case(72): // up
		{
			if (positionOfselectedOption() == 0)
			{
				selectedOption = arrayOfOptions[amountOfOptions - 1];
				draw();
			}
			else
			{
				selectedOption = arrayOfOptions[positionOfselectedOption() - 1];
				draw();
			}
		}
		break;
		case(80): // down
		{
			if (positionOfselectedOption() == amountOfOptions - 1)
			{
				selectedOption = arrayOfOptions[0];
				draw();
			}
			else
			{
				selectedOption = arrayOfOptions[positionOfselectedOption() + 1];
				draw();
			}
		}
		break;
		}
		key = _getch();
	}
}