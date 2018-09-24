#include "LanguagesView.h"


LanguagesView::LanguagesView(Languages l, TypeOfGame t) : View(l, t)
{
	arrayOfOptions = new string[amountOfOptions];
	if (lang == Languages::English)
	{
		arrayOfOptions[0] = "English";
		arrayOfOptions[1] = "Ukrainian";
		arrayOfOptions[2] = "Return to main menu";
	}
	else
	{
		arrayOfOptions[0] = "Англійська";
		arrayOfOptions[1] = "Українська";
		arrayOfOptions[2] = "Повернутись до головного меню";
	}
	selectedOption = arrayOfOptions[0];
}

int LanguagesView::positionOfselectedOption()
{
	for (size_t i = 0; i < amountOfOptions; ++i)
	{
		if (arrayOfOptions[i] == selectedOption)
		{
			return i;
		}
	}
}

View * LanguagesView::nextView()
{
	View * nextV;
	if (selectedOption == arrayOfOptions[1])
	{
		if (lang == Languages::English)
		{
			lang = Languages::Ukrainian;
			nextV = new LanguagesView(lang, type);
		}
		else
		{
			nextV = this;
		}

	}
	else if (selectedOption == arrayOfOptions[0])
	{
		if (lang == Languages::Ukrainian)
		{
			lang = Languages::English;
			nextV = new LanguagesView(lang, type);
			draw();
		}
		else
		{
			nextV = this;
		}
	}
	else
	{
		nextV = new StartView(lang, type);
	}
	return nextV;
}

void LanguagesView::draw()
{
	clean();
	for (size_t i = 0; i < amountOfOptions; ++i)
	{
		if (arrayOfOptions[i] == selectedOption)
		{
			SetConsoleCP(1251);
			SetConsoleOutputCP(1251);
			Printer p(textColor, mainBackgroundColor);
			printAtCenterOfLine(10 + 2 * i, "* " + arrayOfOptions[i] + " *", p, consoleWidth);
		}
		else
		{
			Printer p(mainTextColor, mainBackgroundColor);
			printAtCenterOfLine(10 + 2 * i, arrayOfOptions[i], p, consoleWidth);
		}
	}
}

View * LanguagesView::handle()
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
		break;
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


